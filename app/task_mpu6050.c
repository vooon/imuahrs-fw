/**
 ******************************************************************************
 * @file       pios_mpu000.c
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief      MPU6000 6-axis gyro and accel chip
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

#include "task_mpu6050.h"
#include "protocol.h"

#define MPU6050_I2C_ADDR0		0x68
#define MPU6050_I2C_ADDR1		0x69

/* MPU6000 Addresses */
#define MPU6050_SMPLRT_DIV_REG       0X19
#define MPU6050_DLPF_CFG_REG         0X1A
#define MPU6050_GYRO_CFG_REG         0X1B
#define MPU6050_ACCEL_CFG_REG        0X1C
#define MPU6050_FIFO_EN_REG          0x23
#define MPU6050_INT_CFG_REG          0x37
#define MPU6050_INT_EN_REG           0x38
#define MPU6050_INT_STATUS_REG       0x3A
#define MPU6050_ACCEL_X_OUT_MSB      0x3B
#define MPU6050_ACCEL_X_OUT_LSB      0x3C
#define MPU6050_ACCEL_Y_OUT_MSB      0x3D
#define MPU6050_ACCEL_Y_OUT_LSB      0x3E
#define MPU6050_ACCEL_Z_OUT_MSB      0x3F
#define MPU6050_ACCEL_Z_OUT_LSB      0x40
#define MPU6050_TEMP_OUT_MSB         0x41
#define MPU6050_TEMP_OUT_LSB         0x42
#define MPU6050_GYRO_X_OUT_MSB       0x43
#define MPU6050_GYRO_X_OUT_LSB       0x44
#define MPU6050_GYRO_Y_OUT_MSB       0x45
#define MPU6050_GYRO_Y_OUT_LSB       0x46
#define MPU6050_GYRO_Z_OUT_MSB       0x47
#define MPU6050_GYRO_Z_OUT_LSB       0x48
#define MPU6050_USER_CTRL_REG        0x6A
#define MPU6050_PWR_MGMT_REG         0x6B
#define MPU6050_FIFO_CNT_MSB         0x72
#define MPU6050_FIFO_CNT_LSB         0x73
#define MPU6050_FIFO_REG             0x74
#define MPU6050_WHOAMI               0x75

#define I2C_TIMEOUT	MS2ST(5)
#define EVT_TIMEOUT	MS2ST(50)
#define IRQ_EVTMASK	EVENT_MASK(1)

#define MPU6050_MAX_DOWNSAMPLE 2
struct mpu6050_dev {
    i2caddr_t			addr;
    const struct mpu6050_cfg	*cfg;
    enum mpu6050_range		gyro_range;
    enum mpu6050_accel_range	accel_range;
    enum mpu6050_filter		filter;
};

/* Thread */
static WORKING_AREA(wa_mpu6050, 256);
static msg_t thd_mpu6050(void *arg UNUSED);
static Thread *thdp_mpu6050 = NULL;

// ! Global structure for this device device
static struct mpu6050_dev dev;
static volatile bool mpu6050_configured = false;
static volatile alert_status_t sensor_status = ALST_INIT;


static inline msg_t mpu6050_reg_readm(uint8_t reg, uint8_t *rdbuf, size_t rdsize)
{
	msg_t ret;

	i2cAcquireBus(&I2CD1);
	ret = i2cMasterTransmitTimeout(&I2CD1, dev.addr, &reg, sizeof(reg), rdbuf, rdsize, I2C_TIMEOUT);
	i2cReleaseBus(&I2CD1);

	return ret;
}

static inline msg_t mpu6050_reg_writeb(uint8_t reg, uint8_t val)
{
	uint8_t regbuf[] = { reg, val };
	msg_t ret;

	i2cAcquireBus(&I2CD1);
	ret = i2cMasterTransmitTimeout(&I2CD1, dev.addr, regbuf, sizeof(regbuf), NULL, 0, I2C_TIMEOUT);
	i2cReleaseBus(&I2CD1);

	return ret;
}

/*
 * @brief Read the identification bytes from the MPU6000 sensor
 */
static bool mpu6050_probe(i2caddr_t a)
{
	uint8_t idbuf[2];
	msg_t ret;

	dev.addr = a;

	for (int i = 0; i < 3; i++) {
		ret = mpu6050_reg_readm(MPU6050_WHOAMI, idbuf, 2); /* 2 - hardware bug on F1 */
		if (ret == I2CD_NO_ERROR)
			return idbuf[0] == 0x68;
	}

	return false;
}

/**
 * @brief Initialize the MPU6000 3-axis gyro sensor
 * \return none
 * \param[in] PIOS_MPU6000_ConfigTypeDef struct to be used to configure sensor.
 */
static msg_t mpu6050_config(struct mpu6050_cfg const *cfg)
{
	msg_t ret;
	uint8_t data[2];

	// Reset chip
	ret = mpu6050_reg_writeb(MPU6050_PWR_MGMT_REG, MPU6050_PWRMGMT_IMU_RST);
	if (ret != I2CD_NO_ERROR)
		return ret;

	chThdSleepMilliseconds(50);

	// Reset chip and fifo
	ret = mpu6050_reg_writeb(MPU6050_USER_CTRL_REG,
			MPU6050_USERCTL_GYRO_RST |
			MPU6050_USERCTL_SIG_COND |
			MPU6050_USERCTL_FIFO_RST);
	if (ret != I2CD_NO_ERROR)
		return ret;

	// Wait for reset to finish
	do {
		ret = mpu6050_reg_readm(MPU6050_USER_CTRL_REG, data, 2);
		if (ret != I2CD_NO_ERROR)
			return ret;
		if (!(data[0] & (MPU6050_USERCTL_GYRO_RST | MPU6050_USERCTL_SIG_COND | MPU6050_USERCTL_FIFO_RST)))
			break;
		chThdSleepMilliseconds(5);
	} while(true);

	chThdSleepMilliseconds(10);

	// Power management configuration
	ret = mpu6050_reg_writeb(MPU6050_PWR_MGMT_REG, cfg->Pwr_mgmt_clk);
	if (ret != I2CD_NO_ERROR)
		return ret;

	// Interrupt configuration
	ret = mpu6050_reg_writeb(MPU6050_INT_CFG_REG, cfg->interrupt_cfg);
	if (ret != I2CD_NO_ERROR)
		return ret;

	// Interrupt configuration
	ret = mpu6050_reg_writeb(MPU6050_INT_EN_REG, cfg->interrupt_en);
	if (ret != I2CD_NO_ERROR)
		return ret;

	// FIFO storage
	ret = mpu6050_reg_writeb(MPU6050_FIFO_EN_REG, cfg->Fifo_store);
	if (ret != I2CD_NO_ERROR)
		return ret;

    	mpu6050_configure_ranges(cfg->gyro_range, cfg->accel_range, cfg->filter);

	// Interrupt configuration
	ret = mpu6050_reg_writeb(MPU6050_USER_CTRL_REG, cfg->User_ctl);
	if (ret != I2CD_NO_ERROR)
		return ret;

	ret = mpu6050_reg_writeb(MPU6050_PWR_MGMT_REG, cfg->Pwr_mgmt_clk);
	if (ret != I2CD_NO_ERROR)
		return ret;

	ret = mpu6050_reg_writeb(MPU6050_INT_CFG_REG, cfg->interrupt_cfg);
	if (ret != I2CD_NO_ERROR)
		return ret;

	ret = mpu6050_reg_writeb(MPU6050_INT_EN_REG, cfg->interrupt_en);
	if (ret != I2CD_NO_ERROR)
		return ret;

	ret = mpu6050_reg_readm(MPU6050_INT_EN_REG, data, 2);
	if (ret != I2CD_NO_ERROR)
		return ret;

	if (data[0] != cfg->interrupt_en)
		return RDY_RESET;

	mpu6050_configured = true;
	return RDY_OK;
}

#ifdef MPU6050_USE_FIFO
static msg_t mpu6050_get_fifo_depth(void)
{
	msg_t ret;
	uint8_t data[2];

	ret = mpu6050_reg_readm(MPU6050_FIFO_CNT_MSB, data, sizeof(data));
	if (ret != I2CD_NO_ERROR)
		return ret;

	return data[0] << 8 | data[1];
}
#endif /* MPU6050_USE_FIFO */

/**
 * @brief Initialize the MPU6000 3-axis gyro sensor thread
 */
void mpu6050_init(const struct mpu6050_cfg *cfg)
{
	dev.cfg = cfg;
	thdp_mpu6050 = chThdCreateStatic(wa_mpu6050, sizeof(wa_mpu6050), HIGHPRIO, thd_mpu6050, NULL);
}

static msg_t thd_mpu6050(void *arg UNUSED)
{
	msg_t ret;
	struct mpu6050_data data = { 0, 0, 0, 0, 0, 0, 0 };
	uint8_t databuf[sizeof(data)];

	ALERT_SET_INIT(MPU6050, sensor_status);
	chRegSetThreadName("mpu6050");

	if (!mpu6050_probe(MPU6050_I2C_ADDR0)) {
		/* try find on addr1 */
		if (!mpu6050_probe(MPU6050_I2C_ADDR1)) {
			ALERT_SET_FAIL(MPU6050, sensor_status);
			return -1;
		}
	}

	for (int i = 0; i < 3; i++) {
		ret = mpu6050_config(dev.cfg);
		if (ret == RDY_OK)
			break;

		ALERT_SET_FAIL(MPU6050, sensor_status);
		chThdSleepMilliseconds(10);
	}

	if (ret != RDY_OK || !mpu6050_configured) {
		ALERT_SET_FAIL(MPU6050, sensor_status);
		return -1;
	}

	while (!chThdShouldTerminate()) {
		eventmask_t mask = chEvtWaitOneTimeout(ALL_EVENTS, EVT_TIMEOUT);

		if (!(mask & IRQ_EVTMASK)) {
			if (!mpu6050_probe(dev.addr)) {
				ALERT_SET_FAIL(MPU6050, sensor_status);
				continue;
			}
			/* Regular INT not present, but sensor seems ok.
			 * Read current state. */
		}

#ifdef MPU6050_USE_FIFO
		ret = mpu6050_get_fifo_depth();
		if (ret < 0) {
			ALERT_SET_FAIL(MPU6050, sensor_status);
			continue;
		}
		size_t fifo_count = ret;

		if (fifo_count < sizeof(data))
			continue;

		ret = mpu6050_reg_readm(MPU6050_FIFO_REG, databuf, sizeof(databuf));
		if (ret != I2CD_NO_ERROR)  {
			ALERT_SET_FAIL(MPU6050, sensor_status);
			continue;
		}

		// special case
		if (fifo_count >= sizeof(data) * 2) {
			ret = mpu6050_reg_readm(MPU6050_FIFO_REG, databuf, sizeof(databuf));
			if (ret != I2CD_NO_ERROR)  {
				ALERT_SET_FAIL(MPU6050, sensor_status);
				continue;
			}
		}
#else
		ret = mpu6050_reg_readm(MPU6050_ACCEL_X_OUT_MSB, databuf, sizeof(databuf));
		if (ret != I2CD_NO_ERROR)  {
			ALERT_SET_FAIL(MPU6050, sensor_status);
			continue;
		}
#endif /* MPU6050_USE_FIFO */

		// Rotate the sensor to OP convention.  The datasheet defines X as towards the right
		// and Y as forward.  OP convention transposes this.  Also the Z is defined negatively
		// to our convention
		// Currently we only support rotations on top so switch X/Y accordingly
		switch (dev.cfg->orientation) {
		case MPU6050_TOP_0DEG:
			data.accel_y = databuf[0] << 8	| databuf[1];	// chip X
			data.accel_x = databuf[2] << 8	| databuf[3];	// chip Y
			data.gyro_y  = databuf[8] << 8	| databuf[9];	// chip X
			data.gyro_x  = databuf[10] << 8	| databuf[11];	// chip Y
			break;
		case MPU6050_TOP_90DEG:
			// -1 to bring it back to -32768 +32767 range
			data.accel_y = -1 - (databuf[2] << 8	| databuf[3]);	// chip Y
			data.accel_x =	     databuf[0] << 8	| databuf[1];	// chip X
			data.gyro_y  = -1 - (databuf[10] << 8	| databuf[11]);	// chip Y
			data.gyro_x  =       databuf[8] << 8	| databuf[9];	// chip X
			break;
		case MPU6050_TOP_180DEG:
			data.accel_y = -1 - (databuf[0] << 8	| databuf[1]);	// chip X
			data.accel_x = -1 - (databuf[2] << 8	| databuf[3]);	// chip Y
			data.gyro_y  = -1 - (databuf[8] << 8	| databuf[9]);	// chip X
			data.gyro_x  = -1 - (databuf[10] << 8	| databuf[11]);	// chip Y
			break;
		case MPU6050_TOP_270DEG:
			data.accel_y =       databuf[2] << 8	| databuf[3];	// chip Y
			data.accel_x = -1 - (databuf[0] << 8	| databuf[1]);	// chip X
			data.gyro_y  =       databuf[10] << 8	| databuf[11];	// chip Y
			data.gyro_x  = -1 - (databuf[8] << 8	| databuf[9]);	// chip X
			break;
		}

		data.gyro_z      = -1 - (databuf[12] << 8	| databuf[13]);
		data.accel_z     = -1 - (databuf[4] << 8	| databuf[5]);
		data.temperature =       databuf[6] << 8	| databuf[7];


		ALERT_SET_NORMAL(MPU6050, sensor_status);
		pt_send_mpu_dat(
				data.gyro_x,
				data.gyro_y,
				data.gyro_z,
				data.accel_x,
				data.accel_y,
				data.accel_z,
				data.temperature
			       );
	}

	return 0;
}

alert_status_t mpu6050_get_status(void)
{
	return sensor_status;
}

/**
 * @brief Configures Gyro, accel and Filter ranges/setings
 */
void mpu6050_configure_ranges(
		enum mpu6050_range gyro_range,
		enum mpu6050_accel_range accel_range,
		enum mpu6050_filter filter_setting)
{
	msg_t ret;

	// update filter settings
	ret = mpu6050_reg_writeb(MPU6050_DLPF_CFG_REG, filter_setting);
	if (ret != I2CD_NO_ERROR)
		return;

	// Sample rate divider, chosen upon digital filtering settings
	ret = mpu6050_reg_writeb(MPU6050_SMPLRT_DIV_REG,
			(filter_setting == MPU6050_LOWPASS_256_HZ)?
				dev.cfg->Smpl_rate_div_no_dlp :
				dev.cfg->Smpl_rate_div_dlp);
	if (ret != I2CD_NO_ERROR)
		return;

	dev.filter = filter_setting;

	// Gyro range
	ret = mpu6050_reg_writeb(MPU6050_GYRO_CFG_REG, gyro_range);
	if (ret != I2CD_NO_ERROR)
		return;

	dev.gyro_range = gyro_range;

	// Set the accel range
	ret = mpu6050_reg_writeb(MPU6050_ACCEL_CFG_REG, accel_range);
	if (ret != I2CD_NO_ERROR)
		return;

	dev.accel_range = accel_range;
}

/**
 * EXTI irq handler for MPU6050
 */
void mpu6050_exti_handler(EXTDriver *extp UNUSED, expchannel_t channel UNUSED)
{
	if (!mpu6050_configured || thdp_mpu6050 == NULL)
		return;

	chSysLockFromIsr();
	chEvtSignalI(thdp_mpu6050, IRQ_EVTMASK);
	chSysUnlockFromIsr();
}

