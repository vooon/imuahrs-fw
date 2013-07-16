/**
 ******************************************************************************
 * @file       pios_bmp085.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @brief      BMP085 Pressure Sensor Routines
 * @see        The GNU Public License (GPL) Version 3
 *
 ******************************************************************************/
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

#include "task_bmp085.h"
#include "protocol.h"

/* BMP085 Addresses */
#define BMP085_I2C_ADDR     0x77
#define BMP085_CALIB_ADDR   0xAA
#define BMP085_CALIB_LEN    22
#define BMP085_CTRL_ADDR    0xF4
#define BMP085_ID_ADDR      0xD0
#define BMP085_OVERSAMPLING 3
#define BMP085_PRES_ADDR    (0x34 + (BMP085_OVERSAMPLING << 6))
#define BMP085_TEMP_ADDR    0x2E
#define BMP085_ADC_MSB      0xF6
#define BMP085_P0           101325

#define I2C_TIMEOUT    MS2ST(5)

struct calib_data {
    int16_t  AC1;
    int16_t  AC2;
    int16_t  AC3;
    uint16_t AC4;
    uint16_t AC5;
    uint16_t AC6;
    int16_t  B1;
    int16_t  B2;
    int16_t  MB;
    int16_t  MC;
    int16_t  MD;
};

/* Thread */
static WORKING_AREA(wa_bmp085, 256);
static msg_t thd_bmp085(void *arg UNUSED);

/* Local Variables */
static struct calib_data calib_data;
static volatile alert_status_t sensor_status = ALST_INIT;

/* Straight from the datasheet */
static int32_t X1, X2, X3, B3, B5, B6, P;
static uint32_t B4, B7;
static uint16_t raw_temperature;
static uint32_t raw_pressure;
static uint32_t pressure;
static uint16_t temperature;



static inline msg_t bmp085_reg_readm(uint8_t reg, uint8_t *rdbuf, size_t rdsize)
{
	msg_t ret;

	i2cAcquireBus(&I2CD1);
	ret = i2cMasterTransmitTimeout(&I2CD1, BMP085_I2C_ADDR, &reg, sizeof(reg), rdbuf, rdsize, I2C_TIMEOUT);
	i2cReleaseBus(&I2CD1);

	return ret;
}

static inline msg_t bmp085_reg_writeb(uint8_t reg, uint8_t val)
{
	uint8_t regbuf[] = { reg, val };
	msg_t ret;

	i2cAcquireBus(&I2CD1);
	ret = i2cMasterTransmitTimeout(&I2CD1, BMP085_I2C_ADDR, regbuf, sizeof(regbuf), NULL, 0, I2C_TIMEOUT);
	i2cReleaseBus(&I2CD1);

	return ret;
}

static msg_t bmp085_read_calibration(void)
{
	uint8_t data[BMP085_CALIB_LEN];
	msg_t ret;

	/* Read all 22 bytes of calibration data in one transfer, this is a very optimized way of doing things */
	ret = bmp085_reg_readm(BMP085_CALIB_ADDR, data, sizeof(data));

	if (ret == I2CD_NO_ERROR) {
		/* Parameters AC1-AC6 */
		calib_data.AC1 = (data[0] << 8) | data[1];
		calib_data.AC2 = (data[2] << 8) | data[3];
		calib_data.AC3 = (data[4] << 8) | data[5];
		calib_data.AC4 = (data[6] << 8) | data[7];
		calib_data.AC5 = (data[8] << 8) | data[9];
		calib_data.AC6 = (data[10] << 8) | data[11];

		/* Parameters B1, B2 */
		calib_data.B1  = (data[12] << 8) | data[13];
		calib_data.B2  = (data[14] << 8) | data[15];

		/* Parameters MB, MC, MD */
		calib_data.MB  = (data[16] << 8) | data[17];
		calib_data.MC  = (data[18] << 8) | data[19];
		calib_data.MD  = (data[20] << 8) | data[21];
	}

	return ret;
}

/**
 * Initialise the BMP085 sensor thread
 */
void bmp085_init()
{
	chThdCreateStatic(wa_bmp085, sizeof(wa_bmp085), NORMALPRIO, thd_bmp085, NULL);
}

static msg_t thd_bmp085(void *arg UNUSED)
{
	uint8_t data[3] = { 0, 0, 0 };
	msg_t ret;

	ALERT_SET_INIT(BMP085, sensor_status);
	chRegSetThreadName("bmp085");

	for (int i = 0; i < 3; i++) {
		ret = bmp085_reg_readm(BMP085_ID_ADDR, data, 2); /* 2 - hardware error with 1-byte transfers on F1 */
		if (ret == I2CD_NO_ERROR)
			break;

		ALERT_SET_FAIL(BMP085, sensor_status);
		chThdSleepMilliseconds(10);
	}

	if (data[0] != 0x55 || ret != I2CD_NO_ERROR) {
		ALERT_SET_FAIL(BMP085, sensor_status);
		return -1; /* Not BMP085! exiting */
	}

	while (!chThdShouldTerminate() && bmp085_read_calibration() != I2CD_NO_ERROR) {
		ALERT_SET_FAIL(BMP085, sensor_status);
		chThdSleepMilliseconds(5);
	}

	while (!chThdShouldTerminate()) {
		chThdSleepMilliseconds(10);

		/* start temperature conversion */
		ret = bmp085_reg_writeb(BMP085_CTRL_ADDR, BMP085_TEMP_ADDR);
		if (ret != I2CD_NO_ERROR) {
			ALERT_SET_FAIL(BMP085, sensor_status);
			continue;
		}

		chThdSleepMilliseconds(5);

		ret = bmp085_reg_readm(BMP085_ADC_MSB, data, 2);
		if (ret != I2CD_NO_ERROR) {
			ALERT_SET_FAIL(BMP085, sensor_status);
			continue;
		}

		raw_temperature = ((data[0] << 8) | data[1]);

		X1 = (raw_temperature - calib_data.AC6) * calib_data.AC5 >> 15;
		X2 = ((int32_t)calib_data.MC << 11) / (X1 + calib_data.MD);
		B5 = X1 + X2;
		temperature = (B5 + 8) >> 4;

		/* start pressure conversion */
		ret = bmp085_reg_writeb(BMP085_CTRL_ADDR, BMP085_PRES_ADDR);
		if (ret != I2CD_NO_ERROR) {
			ALERT_SET_FAIL(BMP085, sensor_status);
			continue;
		}

		chThdSleepMilliseconds(26);

		ret = bmp085_reg_readm(BMP085_ADC_MSB, data, 3);
		if (ret != I2CD_NO_ERROR) {
			ALERT_SET_FAIL(BMP085, sensor_status);
			continue;
		}

		raw_pressure = ((data[0] << 16) | (data[1] << 8) | data[2]) >> (8 - BMP085_OVERSAMPLING);

		B6 = B5 - 4000;
		X1 = (calib_data.B2 * (B6 * B6 >> 12)) >> 11;
		X2 = calib_data.AC2 * B6 >> 11;
		X3 = X1 + X2;
		B3 = ((((int32_t)calib_data.AC1 * 4 + X3) << BMP085_OVERSAMPLING) + 2) >> 2;
		X1 = calib_data.AC3 * B6 >> 13;
		X2 = (calib_data.B1 * (B6 * B6 >> 12)) >> 16;
		X3 = ((X1 + X2) + 2) >> 2;
		B4 = (calib_data.AC4 * (uint32_t)(X3 + 32768)) >> 15;
		B7 = ((uint32_t)raw_pressure - B3) * (50000 >> BMP085_OVERSAMPLING);
		P  = B7 < 0x80000000 ? (B7 * 2) / B4 : (B7 / B4) * 2;

		X1 = (P >> 8) * (P >> 8);
		X1 = (X1 * 3038) >> 16;
		X2 = (-7357 * P) >> 16;
		pressure = P + ((X1 + X2 + 3791) >> 4);

		ALERT_SET_NORMAL(BMP085, sensor_status);
		pt_send_bar_dat(pressure, temperature);
	}

	return 0;
}

alert_status_t bmp085_get_status(void)
{
	return sensor_status;
}
