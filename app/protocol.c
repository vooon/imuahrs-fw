/**
 * @file       protocol.c
 * @brief      protocol thread functions
 * @author     Vladimir Ermakov Copyright (C) 2013.
 * @see        The GNU Public License (GPL) Version 3
 */
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "ch.h"
#include "evtimer.h"
#include <string.h>

#include "protocol.h"
#include "pios_crc.h" /* use crc functions from OpenPilot */

#include "task_bmp085.h"
#include "task_hmc5883.h"
#include "task_mpu6050.h"
#include "task_servopwm.h"
#include "task_rpm.h"

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
static volatile bool allow_trm_dat;
static volatile bool allow_rpm_dat;

enum proto_rx_state {
	PR_WAIT_START = 0,
	PR_MSGID,
	PR_TIME_L,
	PR_TIME_H,
	PR_LEN,
	PR_PAYLOAD,
	PR_CRC
};

static const uint8_t fw_version[] = BOARD_NAME " " FW_VERSION " " __DATE__;

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

		ret = sdGetTimeout(&PROTO_SD, SER_TIMEOUT);
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
			ret = sdReadTimeout(&PROTO_SD, pkt_payload, pkt_len, SER_PAYLOAD_TIMEOUT);
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
	ret = sdWriteTimeout(&PROTO_SD, header, sizeof(header), SER_TIMEOUT);
	if (ret == Q_TIMEOUT || ret == Q_RESET)
		goto unlock_ret;

	if (payload_len > 0) {
		crc = PIOS_CRC_updateCRC(crc, payload, payload_len);
		ret = sdWriteTimeout(&PROTO_SD, payload, payload_len, SER_PAYLOAD_TIMEOUT);
		if (ret == Q_TIMEOUT || ret == Q_RESET)
			goto unlock_ret;
	}

	ret = sdPutTimeout(&PROTO_SD, crc, SER_TIMEOUT);

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

#ifdef HAS_DEV_SERVOPWM
	case ID_SERVO_SET:
		if (payload_len % sizeof(struct pt_servo_set)) {
			ret = Q_RESET;
			break;
		}

		for (size_t i = 0; i < payload_len; i += sizeof(struct pt_servo_set)) {
			struct pt_servo_set servo_set;
			memcpy(&servo_set, payload, sizeof(servo_set));
			servopwm_set_channel(servo_set.channel, servo_set.pulse);
		}

		break;
#endif

#ifdef HAS_DEV_RPM
	case ID_ENGINE_STOP:
		rpm_stop_engine(payload[0]);
		break;
#endif

	case ID_MESG_EN:
		if (payload_len != 1) {
			ret = Q_RESET;
			break;
		}

		allow_mpu_dat = payload[0] & 0x01;
		allow_mag_dat = payload[0] & 0x02;
		allow_bar_dat = payload[0] & 0x04;
		allow_trm_dat = payload[0] & 0x08;
		allow_rpm_dat = payload[0] & 0x10;

		if (!allow_mpu_dat && !allow_mag_dat && !allow_bar_dat) {
			evtStart(&heartbeat_et);
		}
		else {
			evtStop(&heartbeat_et);
		}
		break;

	case ID_MPU_CFG:
		if (payload_len == 3) {
			ret = Q_RESET;
			break;
		}

		mpu6050_configure_ranges(payload[0], payload[1], payload[2]);
		break;

	case ID_HMC_CFG:
		hmc5883_reconfigure(); /* placeholder */
		break;

	case ID_BMP_CFG:
		bmp085_reconfigure(); /* placeholder */
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
	uint8_t prev_state = sens_test_state;

	sens_test_state =
		((mpu == ALST_NORMAL)? 0x3 : 0) |	/* GYRO_OK | ACCEL_OK */
		((hmc == ALST_NORMAL)? 0x4 : 0) |	/* MAG_OK */
		((bmp == ALST_NORMAL)? 0x8 : 0);	/* BARO_OK */

	/* send notification if changed */
	if (prev_state != sens_test_state)
		pt_send_pkt(ID_SENS_TEST, (const uint8_t *)&sens_test_state, sizeof(sens_test_state));
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

void pt_send_trm_dat(int16_t temperature)
{
	msg_t ret;
	struct pt_trm_dat data = { .temperature = temperature };

	if (!allow_trm_dat)
		return;

	ret = pt_send_pkt(ID_TRM_DAT, (uint8_t *)&data, sizeof(data));
	if (ret == Q_TIMEOUT || ret == Q_RESET) {
		ALERT_SET_FAIL(PROTO, protocol_status);
	}
}

void pt_send_rpm_dat(uint16_t rpm)
{
	msg_t ret;
	struct pt_rpm_dat data = { .rpm = rpm };

	if (!allow_rpm_dat)
		return;

	ret = pt_send_pkt(ID_RPM_DAT, (uint8_t *)&data, sizeof(data));
	if (ret == Q_TIMEOUT || ret == Q_RESET) {
		ALERT_SET_FAIL(PROTO, protocol_status);
	}
}
