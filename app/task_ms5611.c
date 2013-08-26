/**
 ******************************************************************************
 * @file       pios_ms5611.c
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

#include "task_ms5611.h"
#include "protocol.h"

/* MS5611 Addresses */
#define MS5611_I2C_ADDR     0x77
#define MS5611_RESET      0x1E
#define MS5611_CALIB_ADDR 0xA2 /* First sample is factory stuff */
#define MS5611_CALIB_LEN  16
#define MS5611_ADC_READ   0x00
#define MS5611_PRES_ADDR  0x40
#define MS5611_TEMP_ADDR  0x50
#define MS5611_P0         101.3250f

#define I2C_TIMEOUT    MS2ST(5)

struct calib_data {
    uint16_t C[6];
};

/* Thread */
static WORKING_AREA(wa_ms5611, 256);
static msg_t thd_ms5611(void *arg UNUSED);

/* Local Variables */
static struct calib_data calib_data;
static const struct ms5611_cfg *dev_cfg;
static volatile alert_status_t sensor_status = ALST_INIT;
static uint32_t oversampling;

/* Straight from the datasheet */
static int32_t raw_temperature;
static int32_t raw_pressure;
static int64_t pressure;
static int64_t temperature;



static inline msg_t ms5611_reg_readm(uint8_t reg, uint8_t *rdbuf, size_t rdsize)
{
	msg_t ret;

	i2cAcquireBus(&I2CD1);
	ret = i2cMasterTransmitTimeout(&I2CD1, MS5611_I2C_ADDR, &reg, sizeof(reg), rdbuf, rdsize, I2C_TIMEOUT);
	i2cReleaseBus(&I2CD1);

	return ret;
}

static inline msg_t ms5611_reg_writec(uint8_t val)
{
	msg_t ret;

	i2cAcquireBus(&I2CD1);
	ret = i2cMasterTransmitTimeout(&I2CD1, MS5611_I2C_ADDR, &val, sizeof(val), NULL, 0, I2C_TIMEOUT);
	i2cReleaseBus(&I2CD1);

	return ret;
}

static inline uint32_t ms5611_get_delay_us(void)
{
	switch (oversampling) {
	case MS5611_OSR_256:
		return 600;

	case MS5611_OSR_512:
		return 1170;

	case MS5611_OSR_1024:
		return 2280;

	case MS5611_OSR_2048:
		return 4540;

	case MS5611_OSR_4096:
		return 9040;

	default:
		break;
	}

	return 10;
}

static msg_t ms5611_read_calibration(void)
{
	uint8_t data[2];
	msg_t ret;

	for (int i = 0; i < 6; i++) {
		ret = ms5611_reg_readm(MS5611_CALIB_ADDR + i * 2, data, sizeof(data));

		if (ret == I2CD_NO_ERROR)
			calib_data.C[i] = (data[0] << 8) | data[1];
		else
			break;
	}

	return ret;
}

/**
 * Initialise the BMP085 sensor thread
 */
void ms5611_init(const struct ms5611_cfg *cfg)
{
	dev_cfg = cfg;
	oversampling = cfg->oversampling;

	chThdCreateStatic(wa_ms5611, sizeof(wa_ms5611), HIGHPRIO, thd_ms5611, NULL);
}

static msg_t thd_ms5611(void *arg UNUSED)
{
	uint8_t data[3] = { 0, 0, 0 };
	int64_t delta_temp;
        int64_t offset;
        int64_t sens;
	msg_t ret;

	ALERT_SET_INIT(BMP085, sensor_status);
	chRegSetThreadName("ms5611");

	for (int i = 0; i < 3; i++) {
		ret = ms5611_reg_writec(MS5611_RESET);
		if (ret == I2CD_NO_ERROR)
			break;

		ALERT_SET_FAIL(BMP085, sensor_status);
		chThdSleepMilliseconds(50);
	}

	if (ret != I2CD_NO_ERROR) {
			ALERT_SET_FAIL(BMP085, sensor_status);
			return -1; /* MS5611 not exist! */
	}

	chThdSleepMilliseconds(20);

	while (!chThdShouldTerminate() && ms5611_read_calibration() != I2CD_NO_ERROR) {
		ALERT_SET_FAIL(BMP085, sensor_status);
		chThdSleepMilliseconds(5);
	}

	while (!chThdShouldTerminate()) {
		chThdSleepMilliseconds(100);

		/* start temperature conversion */
		ret = ms5611_reg_writec(MS5611_TEMP_ADDR + oversampling);
		if (ret != I2CD_NO_ERROR) {
			ALERT_SET_FAIL(BMP085, sensor_status);
			continue;
		}

		chThdSleepMicroseconds(ms5611_get_delay_us());

		ret = ms5611_reg_readm(MS5611_ADC_READ, data, 3);
		if (ret != I2CD_NO_ERROR) {
			ALERT_SET_FAIL(BMP085, sensor_status);
			continue;
		}

		raw_temperature = (data[0] << 16) | (data[1] << 8) | data[0];

		delta_temp = raw_temperature - (calib_data.C[4] << 8);
		temperature = 2000l + ((delta_temp * calib_data.C[5]) >> 23);

		/* start pressure conversion */
		ret = ms5611_reg_writec(MS5611_PRES_ADDR + oversampling);
		if (ret != I2CD_NO_ERROR) {
			ALERT_SET_FAIL(BMP085, sensor_status);
			continue;
		}

		chThdSleepMicroseconds(ms5611_get_delay_us());

		ret = ms5611_reg_readm(MS5611_ADC_READ, data, 3);
		if (ret != I2CD_NO_ERROR) {
			ALERT_SET_FAIL(BMP085, sensor_status);
			continue;
		}

		raw_pressure = (data[0] << 16) | (data[1] << 8) | data[2];

		offset   = (((int64_t)calib_data.C[1]) << 16) + ((((int64_t)calib_data.C[3]) * delta_temp) >> 7);
		sens     = ((int64_t)calib_data.C[0]) << 15;
		sens     = sens + ((((int64_t)calib_data.C[2]) * delta_temp) >> 8);

		pressure = (((((int64_t)raw_pressure) * sens) >> 21) - offset) >> 15;

		ALERT_SET_NORMAL(BMP085, sensor_status);
		pt_send_bar_dat(pressure, temperature);
	}

	return 0;
}

alert_status_t ms5611_get_status(void)
{
	return sensor_status;
}
