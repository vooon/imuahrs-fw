
#include "ch.h"
#include "evtimer.h"
#include "protocol.h"
#include "pios_crc.h" /* use crc functions from OpenPilot */

#include "task_bmp085.h"
//#include "task_hmc5883.h"
//#include "task_mpu6050.h"

/* Thread */
static WORKING_AREA(wa_protocol, 1024);
static msg_t thd_protocol(void *arg UNUSED);
static void pt_process_pkt(uint8_t msgid, uint16_t time, const uint8_t *payload, size_t payload_len);
static msg_t pt_send_pkt(uint8_t msgid, const uint8_t *payload, size_t payload_len);

/* Local variables */
static volatile alert_status_t protocol_status = ALST_INIT;
static MUTEX_DECL(tx_mutex);
static EvTimer heartbeat_et;

static volatile uint8_t sens_test_state;
static volatile bool allow_mpu_dat;
static volatile bool allow_mag_dat;
static volatile bool allow_bar_dat;

enum proto_rx_state {
	PR_WAIT_START = 0,
	PR_MSGID,
	PR_TIME_L,
	PR_TIME_H,
	PR_LEN,
	PR_PAYLOAD,
	PR_CRC
};

static const uint8_t fw_version[] = "IMU AHRS 0.0.0 " __DATE__;

#define PROTO_START		0x79
#define MAX_PAYLOAD		255

#define SER_TIMEOUT		MS2ST(10)
#define SER_PAYLOAD_TIMEOUT	MS2ST(20)
#define HEARTBEAT_TIMEOUT	MS2ST(1000)


void pt_init(void)
{
	chThdCreateStatic(wa_protocol, sizeof(wa_protocol), NORMALPRIO, thd_protocol, NULL);
}

static msg_t thd_protocol(void *arg UNUSED)
{
	msg_t ret;
	uint8_t msgid = 0;
	uint16_t pkt_time = 0;
	size_t pkt_len = 0;
	uint8_t pkt_payload[MAX_PAYLOAD];
	uint8_t pkt_crc = 0;
	enum proto_rx_state rx_state = PR_WAIT_START;
	EventListener el0;

	evtInit(&heartbeat_et, HEARTBEAT_TIMEOUT);
	chEvtRegister(&heartbeat_et.et_es, &el0, 0);

	evtStart(&heartbeat_et);

	while (!chThdShouldTerminate()) {
		eventmask_t mask = chEvtGetAndClearEvents(ALL_EVENTS);

		if (mask & EVENT_MASK(0)) {
			pt_send_pkt(ID_HEARTBEAT, NULL, 0);
		}

		ret = sdGetTimeout(&SD2, SER_TIMEOUT);
		if (ret == Q_TIMEOUT || ret == Q_RESET)
			continue;

		switch (rx_state) {
		case PR_WAIT_START:
			if (ret == PROTO_START) {
				rx_state = PR_MSGID;
			}
			break;

		case PR_MSGID:
			msgid = ret;
			pkt_crc = PIOS_CRC_updateByte(0, ret);
			rx_state = PR_TIME_L;
			break;

		case PR_TIME_L:
			pkt_time = (uint8_t) ret;
			pkt_crc = PIOS_CRC_updateByte(pkt_crc, ret);
			rx_state = PR_TIME_H;
			break;

		case PR_TIME_H:
			pkt_time |= ((uint8_t) ret) << 8;
			pkt_crc = PIOS_CRC_updateByte(pkt_crc, ret);
			rx_state = PR_LEN;
			break;

		case PR_LEN:
			pkt_len = (uint8_t) ret;
			pkt_crc = PIOS_CRC_updateByte(pkt_crc, ret);
			rx_state = PR_PAYLOAD;
			if (pkt_len == 0) {
				rx_state = PR_CRC;
				break;
			}
			/* fall through if payload exists */

		case PR_PAYLOAD:
			ret = sdReadTimeout(&SD2, pkt_payload, pkt_len, SER_PAYLOAD_TIMEOUT);
			if (ret == Q_TIMEOUT || ret == Q_RESET) {
				rx_state = PR_WAIT_START;
				ALERT_SET_FAIL(PROTO, protocol_status);
				break;
			}

			pkt_crc = PIOS_CRC_updateCRC(pkt_crc, pkt_payload, pkt_len);
			rx_state = PR_CRC;
			break;

		case PR_CRC:
			/* check crc && process pkt */
			if (pkt_crc == ret) {
				pt_process_pkt(msgid, pkt_time, pkt_payload, pkt_len);
			} else {
				ALERT_SET_FAIL(PROTO, protocol_status);
			}

			rx_state = PR_WAIT_START;
			break;

		default:
			rx_state = PR_WAIT_START;
		}
	}

	return 0;
}

alert_status_t pt_get_status(void)
{
	return protocol_status;
}

static msg_t pt_send_pkt(uint8_t msgid, const uint8_t *payload, size_t payload_len)
{
	msg_t ret;
	uint8_t crc;
	uint16_t time = chTimeNow() * 1000 / CH_FREQUENCY; /* systime -> msec */
	uint8_t header[] = { PROTO_START, msgid, time & 0xff, time >> 8, payload_len };

	chMtxLock(&tx_mutex);

	crc = PIOS_CRC_updateCRC(0, header + 1, sizeof(header) - 1);
	ret = sdWriteTimeout(&SD2, header, sizeof(header), SER_TIMEOUT);
	if (ret == Q_TIMEOUT || ret == Q_RESET)
		goto unlock_ret;

	if (payload_len > 0) {
		crc = PIOS_CRC_updateCRC(crc, payload, payload_len);
		ret = sdWriteTimeout(&SD2, payload, payload_len, SER_PAYLOAD_TIMEOUT);
		if (ret == Q_TIMEOUT || ret == Q_RESET)
			goto unlock_ret;
	}

	ret = sdPutTimeout(&SD2, crc, SER_TIMEOUT);

unlock_ret:
	chMtxUnlock();
	return ret;
}

void pt_process_pkt(uint8_t msgid, uint16_t time UNUSED, const uint8_t *payload, size_t payload_len)
{
	msg_t ret = RDY_OK;

	switch (msgid) {
	case ID_VERSION:
		ret = pt_send_pkt(msgid, fw_version, sizeof(fw_version));
		break;

	case ID_SENS_TEST:
		ret = pt_send_pkt(msgid, (const uint8_t *)&sens_test_state, sizeof(sens_test_state));
		break;

	case ID_MESG_EN:
		if (payload_len != 1) {
			ret = Q_RESET;
			break;
		}

		allow_mpu_dat = payload[0] & 0x01;
		allow_mag_dat = payload[0] & 0x02;
		allow_bar_dat = payload[0] & 0x04;

		if (!allow_mpu_dat && !allow_mag_dat && !allow_bar_dat) {
			evtStart(&heartbeat_et);
		}
		else {
			evtStop(&heartbeat_et);
		}
		break;

	case ID_MPU_CFG:
		/* TODO */
		break;

	case ID_HMC_CFG:
		/* TODO */
		break;

	case ID_BMP_CFG:
		bmp085_reconfigure();
		break;

	default:
		ret = Q_RESET; /* unknown or forbidden id */
	}


	if (ret == Q_TIMEOUT || ret == Q_RESET) {
		ALERT_SET_FAIL(PROTO, protocol_status);
	}
	else {
		if (!allow_mpu_dat && !allow_mag_dat && !allow_bar_dat)
			ALERT_SET_INIT(PROTO, protocol_status);
		else
			ALERT_SET_NORMAL(PROTO, protocol_status);
	}
}

void pt_set_sens_state(alert_status_t mpu, alert_status_t hmc, alert_status_t bmp)
{
	sens_test_state =
		((mpu == ALST_NORMAL)? 0x3 : 0) |	/* GYRO_OK | ACCEL_OK */
		((hmc == ALST_NORMAL)? 0x4 : 0) |	/* MAG_OK */
		((bmp == ALST_NORMAL)? 0x8 : 0);	/* BARO_OK */
}

void pt_send_mpu_dat(int16_t gx, int16_t gy, int16_t gz, int16_t ax, int16_t ay, int16_t az, int16_t temp)
{
	msg_t ret;
	struct pt_mpu_dat data = {
		.gyro_x = gx,
		.gyro_y = gy,
		.gyro_z = gz,
		.accel_x = ax,
		.accel_y = ay,
		.accel_z = az,
		.temperature = temp
	};

	if (!allow_mpu_dat)
		return;

	ret = pt_send_pkt(ID_MPU_DAT, (uint8_t *)&data, sizeof(data));
	if (ret == Q_TIMEOUT || ret == Q_RESET) {
		ALERT_SET_FAIL(PROTO, protocol_status);
	}
}

void pt_send_mag_dat(int16_t mag_x, int16_t mag_y, int16_t mag_z)
{
	msg_t ret;
	struct pt_mag_dat data = { .mag_x = mag_x, .mag_y = mag_y, .mag_z = mag_z };

	if (!allow_mag_dat)
		return;

	ret = pt_send_pkt(ID_MAG_DAT, (uint8_t *)&data, sizeof(data));
	if (ret == Q_TIMEOUT || ret == Q_RESET) {
		ALERT_SET_FAIL(PROTO, protocol_status);
	}
}

void pt_send_bar_dat(int32_t pressure, int16_t temperature)
{
	msg_t ret;
	struct pt_bar_dat data = { .pressure = pressure, .temperature = temperature };

	if (!allow_bar_dat)
		return;

	ret = pt_send_pkt(ID_BAR_DAT, (uint8_t *)&data, sizeof(data));
	if (ret == Q_TIMEOUT || ret == Q_RESET) {
		ALERT_SET_FAIL(PROTO, protocol_status);
	}
}

