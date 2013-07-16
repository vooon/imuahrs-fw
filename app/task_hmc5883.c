/**
 ******************************************************************************
 * @file       pios_hmc5883.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief      HMC5883 Magnetic Sensor Functions from AHRS
 * @see        The GNU Public License (GPL) Version 3
 *
 ******************************************************************************
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

#include "task_hmc5883.h"
#include "protocol.h"

/* HMC5883 Addresses */
#define HMC5883_I2C_ADDR           0x1E
#define HMC5883_CONFIG_REG_A       0x00
#define HMC5883_CONFIG_REG_B       0x01
#define HMC5883_MODE_REG           0x02
#define HMC5883_DATAOUT_XMSB_REG   0x03
#define HMC5883_DATAOUT_XLSB_REG   0x04
#define HMC5883_DATAOUT_ZMSB_REG   0x05
#define HMC5883_DATAOUT_ZLSB_REG   0x06
#define HMC5883_DATAOUT_YMSB_REG   0x07
#define HMC5883_DATAOUT_YLSB_REG   0x08
#define HMC5883_DATAOUT_STATUS_REG 0x09
#define HMC5883_DATAOUT_IDA_REG    0x0A
#define HMC5883_DATAOUT_IDB_REG    0x0B
#define HMC5883_DATAOUT_IDC_REG    0x0C

/* Sensitivity Conversion Values */
#define HMC5883_Sensitivity_0_88Ga 1370 // LSB/Ga
#define HMC5883_Sensitivity_1_3Ga  1090    // LSB/Ga
#define HMC5883_Sensitivity_1_9Ga  820     // LSB/Ga
#define HMC5883_Sensitivity_2_5Ga  660     // LSB/Ga
#define HMC5883_Sensitivity_4_0Ga  440     // LSB/Ga
#define HMC5883_Sensitivity_4_7Ga  390     // LSB/Ga
#define HMC5883_Sensitivity_5_6Ga  330     // LSB/Ga
#define HMC5883_Sensitivity_8_1Ga  230     // LSB/Ga  --> NOT RECOMMENDED

#define I2C_TIMEOUT	MS2ST(5)
#define EVT_TIMEOUT	MS2ST(50)
#define IRQ_EVTMASK	EVENT_MASK(2)

/* Thread */
static WORKING_AREA(wa_hmc5883, 256);
static msg_t thd_hmc5883(void *arg UNUSED);
static Thread *thdp_hmc5883 = NULL;

// ! Global structure for this device device
static const struct hmc5883_cfg *dev_cfg;
static volatile bool hmc5883_configured = false;
static volatile alert_status_t sensor_status = ALST_INIT;
static uint8_t CTRLB = 0x00;


static inline msg_t hmc5883_reg_readm(uint8_t reg, uint8_t *rdbuf, size_t rdsize)
{
	msg_t ret;

	i2cAcquireBus(&I2CD1);
	ret = i2cMasterTransmitTimeout(&I2CD1, HMC5883_I2C_ADDR, &reg, sizeof(reg), rdbuf, rdsize, I2C_TIMEOUT);
	i2cReleaseBus(&I2CD1);

	return ret;
}

static inline msg_t hmc5883_reg_writeb(uint8_t reg, uint8_t val)
{
	uint8_t regbuf[] = { reg, val };
	msg_t ret;

	i2cAcquireBus(&I2CD1);
	ret = i2cMasterTransmitTimeout(&I2CD1, HMC5883_I2C_ADDR, regbuf, sizeof(regbuf), NULL, 0, I2C_TIMEOUT);
	i2cReleaseBus(&I2CD1);

	return ret;
}

/*
 * @brief Read the identification bytes from the HMC5883 sensor
 */
static bool hmc5883_probe(void)
{
	uint8_t idbuf[3];
	msg_t ret;

	for (int i = 0; i < 3; i++) {
		ret = hmc5883_reg_readm(HMC5883_DATAOUT_IDA_REG, idbuf, sizeof(idbuf));
		if (ret == I2CD_NO_ERROR)
			return idbuf[0] == 'H' && idbuf[1] == '4' && idbuf[2] == '3';
	}

	return false;
}

/**
 * @brief Initialize the HMC5883 magnetometer sensor
 * \return none
 * \param[in] PIOS_HMC5883_ConfigTypeDef struct to be used to configure sensor.
 *
 * CTRL_REGA: Control Register A
 * Read Write
 * Default value: 0x10
 * 7:5  0   These bits must be cleared for correct operation.
 * 4:2 DO2-DO0: Data Output Rate Bits
 *             DO2 |  DO1 |  DO0 |   Minimum Data Output Rate (Hz)
 *            ------------------------------------------------------
 *              0  |  0   |  0   |            0.75
 *              0  |  0   |  1   |            1.5
 *              0  |  1   |  0   |            3
 *              0  |  1   |  1   |            7.5
 *              1  |  0   |  0   |           15 (default)
 *              1  |  0   |  1   |           30
 *              1  |  1   |  0   |           75
 *              1  |  1   |  1   |           Not Used
 * 1:0 MS1-MS0: Measurement Configuration Bits
 *             MS1 | MS0 |   MODE
 *            ------------------------------
 *              0  |  0   |  Normal
 *              0  |  1   |  Positive Bias
 *              1  |  0   |  Negative Bias
 *              1  |  1   |  Not Used
 *
 * CTRL_REGB: Control RegisterB
 * Read Write
 * Default value: 0x20
 * 7:5 GN2-GN0: Gain Configuration Bits.
 *             GN2 |  GN1 |  GN0 |   Mag Input   | Gain       | Output Range
 *                 |      |      |  Range[Ga]    | [LSB/mGa]  |
 *            ------------------------------------------------------
 *              0  |  0   |  0   |  ±0.88Ga      |   1370     | 0xF8000x07FF (-2048:2047)
 *              0  |  0   |  1   |  ±1.3Ga (def) |   1090     | 0xF8000x07FF (-2048:2047)
 *              0  |  1   |  0   |  ±1.9Ga       |   820      | 0xF8000x07FF (-2048:2047)
 *              0  |  1   |  1   |  ±2.5Ga       |   660      | 0xF8000x07FF (-2048:2047)
 *              1  |  0   |  0   |  ±4.0Ga       |   440      | 0xF8000x07FF (-2048:2047)
 *              1  |  0   |  1   |  ±4.7Ga       |   390      | 0xF8000x07FF (-2048:2047)
 *              1  |  1   |  0   |  ±5.6Ga       |   330      | 0xF8000x07FF (-2048:2047)
 *              1  |  1   |  1   |  ±8.1Ga       |   230      | 0xF8000x07FF (-2048:2047)
 *                               |Not recommended|
 *
 * 4:0 CRB4-CRB: 0 This bit must be cleared for correct operation.
 *
 * _MODE_REG: Mode Register
 * Read Write
 * Default value: 0x02
 * 7:2  0   These bits must be cleared for correct operation.
 * 1:0 MD1-MD0: Mode Select Bits
 *             MS1 | MS0 |   MODE
 *            ------------------------------
 *              0  |  0   |  Continuous-Conversion Mode.
 *              0  |  1   |  Single-Conversion Mode
 *              1  |  0   |  Negative Bias
 *              1  |  1   |  Sleep Mode
 */
static msg_t hmc5883_config(struct hmc5883_cfg const *cfg)
{
	msg_t ret;

	uint8_t CTRLA = 0x00;
	uint8_t MODE  = 0x00;

	CTRLB  = 0;

	CTRLA |= (uint8_t)(cfg->M_ODR | cfg->Meas_Conf);
	CTRLB |= (uint8_t)(cfg->Gain);
	MODE  |= (uint8_t)(cfg->Mode);

	ret = hmc5883_reg_writeb(HMC5883_CONFIG_REG_A, CTRLA);
	if (ret != I2CD_NO_ERROR)
		return ret;

	ret = hmc5883_reg_writeb(HMC5883_CONFIG_REG_B, CTRLB);
	if (ret != I2CD_NO_ERROR)
		return ret;

	ret = hmc5883_reg_writeb(HMC5883_MODE_REG, MODE);
	if (ret != I2CD_NO_ERROR)
		return ret;

	hmc5883_configured = true;
	return RDY_OK;
}

/**
 * @brief Initialize the HMC5883 sensor thread
 */
void hmc5883_init(const struct hmc5883_cfg *cfg)
{
	dev_cfg = cfg;
	thdp_hmc5883 = chThdCreateStatic(wa_hmc5883, sizeof(wa_hmc5883), NORMALPRIO, thd_hmc5883, NULL);
}

static msg_t thd_hmc5883(void *arg UNUSED)
{
	msg_t ret;
	int16_t mag_x, mag_y, mag_z;
	uint8_t databuf[6];
	int32_t sensitivity;

	ALERT_SET_INIT(HMC5883, sensor_status);
	chRegSetThreadName("hmc5883");

	if (!hmc5883_probe()) {
		ALERT_SET_FAIL(HMC5883, sensor_status);
		return -1;
	}

	/* TODO: self test??? */

	for (int i = 0; i < 3; i++) {
		ret = hmc5883_config(dev_cfg);
		if (ret == RDY_OK)
			break;

		ALERT_SET_FAIL(HMC5883, sensor_status);
		chThdSleepMilliseconds(10);
	}

	if (ret != RDY_OK || !hmc5883_configured) {
		ALERT_SET_FAIL(HMC5883, sensor_status);
		return -1;
	}

	while (!chThdShouldTerminate()) {
		eventmask_t mask = chEvtWaitOneTimeout(ALL_EVENTS, EVT_TIMEOUT);

		if (!(mask & IRQ_EVTMASK)) {
			ALERT_SET_FAIL(HMC5883, sensor_status);
			continue;
		}

		ret = hmc5883_reg_readm(HMC5883_DATAOUT_XMSB_REG, databuf, 6);
		if (ret != I2CD_NO_ERROR) {
			ALERT_SET_FAIL(HMC5883, sensor_status);
			continue;
		}

		switch (CTRLB & 0xE0) {
		case 0x00:
			sensitivity = 1000 / HMC5883_Sensitivity_0_88Ga;
			break;
		case 0x20:
			sensitivity = 1000 / HMC5883_Sensitivity_1_3Ga;
			break;
		case 0x40:
			sensitivity = 1000 / HMC5883_Sensitivity_1_9Ga;
			break;
		case 0x60:
			sensitivity = 1000 / HMC5883_Sensitivity_2_5Ga;
			break;
		case 0x80:
			sensitivity = 1000 / HMC5883_Sensitivity_4_0Ga;
			break;
		case 0xA0:
			sensitivity = 1000 / HMC5883_Sensitivity_4_7Ga;
			break;
		case 0xC0:
			sensitivity = 1000 / HMC5883_Sensitivity_5_6Ga;
			break;
		case 0xE0:
			sensitivity = 1000 / HMC5883_Sensitivity_8_1Ga;
			break;
		default:
			ALERT_SET_FAIL(HMC5883, sensor_status);
			continue;
		}

		mag_x = (databuf[0] << 8 | databuf[1]) * sensitivity;
		mag_y = (databuf[2] << 8 | databuf[3]) * sensitivity;
		mag_z = (databuf[4] << 8 | databuf[5]) * sensitivity;

		// This should not be necessary but for some reason it is coming out of continuous conversion mode
		ret = hmc5883_reg_writeb(HMC5883_MODE_REG, HMC5883_MODE_CONTINUOUS);
		if (ret != I2CD_NO_ERROR) {
			ALERT_SET_FAIL(HMC5883, sensor_status);
			continue;
		}

		ALERT_SET_NORMAL(HMC5883, sensor_status);
		pt_send_mag_dat(mag_x, mag_y, mag_z);
	}

	return 0;
}

alert_status_t hmc5883_get_status(void)
{
	return sensor_status;
}

/**
 * EXTI irq handler for HMC5883
 */
void hmc5883_exti_handler(EXTDriver *extp UNUSED, expchannel_t channel UNUSED)
{
	if (!hmc5883_configured || thdp_hmc5883 == NULL)
		return;

	chSysLockFromIsr();
	chEvtSignalI(thdp_hmc5883, IRQ_EVTMASK);
	chSysUnlockFromIsr();
}

