/**
 ******************************************************************************
 * @file       MPU6050.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief      MPU6000 3-axis gyro function headers
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

#ifndef TASK_MPU6050_H
#define TASK_MPU6050_H

#include "hal.h"
#include "alert.h"

/* FIFO enable for storing different values */
#define MPU6050_FIFO_TEMP_OUT        0x80
#define MPU6050_FIFO_GYRO_X_OUT      0x40
#define MPU6050_FIFO_GYRO_Y_OUT      0x20
#define MPU6050_FIFO_GYRO_Z_OUT      0x10
#define MPU6050_ACCEL_OUT            0x08

/* Interrupt Configuration */
#define MPU6050_INT_ACTL             0x80
#define MPU6050_INT_OPEN             0x40
#define MPU6050_INT_LATCH_EN         0x20
#define MPU6050_INT_CLR_ANYRD        0x10
#define MPU6050_INT_I2C_BAYPASS_EN   0x02

#define MPU6050_INTEN_OVERFLOW       0x10
#define MPU6050_INTEN_DATA_RDY       0x01

/* Interrupt status */
#define MPU6050_INT_STATUS_FIFO_FULL 0x80
#define MPU6050_INT_STATUS_IMU_RDY   0X04
#define MPU6050_INT_STATUS_DATA_RDY  0X01

/* User control functionality */
#define MPU6050_USERCTL_FIFO_EN      0X40
#define MPU6050_USERCTL_I2C_MST_EN   0x20
#define MPU6050_USERCTL_DIS_I2C      0X10
#define MPU6050_USERCTL_FIFO_RST     0X04
#define MPU6050_USERCTL_SIG_COND     0X02
#define MPU6050_USERCTL_GYRO_RST     0X01

/* Power management and clock selection */
#define MPU6050_PWRMGMT_IMU_RST      0X80
#define MPU6050_PWRMGMT_INTERN_CLK   0X00
#define MPU6050_PWRMGMT_PLL_X_CLK    0X01
#define MPU6050_PWRMGMT_PLL_Y_CLK    0X02
#define MPU6050_PWRMGMT_PLL_Z_CLK    0X03
#define MPU6050_PWRMGMT_STOP_CLK     0X07


enum mpu6050_range {
	MPU6050_SCALE_250_DEG  = 0x00,
	MPU6050_SCALE_500_DEG  = 0x08,
	MPU6050_SCALE_1000_DEG = 0x10,
	MPU6050_SCALE_2000_DEG = 0x18
};

enum mpu6050_filter {
	MPU6050_LOWPASS_256_HZ = 0x00,
	MPU6050_LOWPASS_188_HZ = 0x01,
	MPU6050_LOWPASS_98_HZ  = 0x02,
	MPU6050_LOWPASS_42_HZ  = 0x03,
	MPU6050_LOWPASS_20_HZ  = 0x04,
	MPU6050_LOWPASS_10_HZ  = 0x05,
	MPU6050_LOWPASS_5_HZ   = 0x06
};

enum mpu6050_accel_range {
	MPU6050_ACCEL_2G  = 0x00,
	MPU6050_ACCEL_4G  = 0x08,
	MPU6050_ACCEL_8G  = 0x10,
	MPU6050_ACCEL_16G = 0x18
};

enum mpu6050_orientation { // clockwise rotation from board forward
	MPU6050_TOP_0DEG   = 0x00,
	MPU6050_TOP_90DEG  = 0x01,
	MPU6050_TOP_180DEG = 0x02,
	MPU6050_TOP_270DEG = 0x03
};

struct mpu6050_data {
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	int16_t temperature;
};

struct mpu6050_cfg {
	uint8_t Fifo_store; /* FIFO storage of different readings (See datasheet page 31 for more details) */

	/* Sample rate divider to use (See datasheet page 32 for more details).*/
	uint8_t Smpl_rate_div_no_dlp; /* used when no dlp is applied (fs=8KHz)*/
	uint8_t Smpl_rate_div_dlp; /* used when dlp is on (fs=1kHz)*/
	uint8_t interrupt_cfg; /* Interrupt configuration (See datasheet page 35 for more details) */
	uint8_t interrupt_en; /* Interrupt configuration (See datasheet page 35 for more details) */
	uint8_t User_ctl; /* User control settings (See datasheet page 41 for more details)  */
	uint8_t Pwr_mgmt_clk; /* Power management and clock selection (See datasheet page 32 for more details) */
	enum mpu6050_accel_range accel_range;
	enum mpu6050_range gyro_range;
	enum mpu6050_filter filter;
	enum mpu6050_orientation orientation;
};

/* Public Functions */
extern void mpu6050_init(const struct mpu6050_cfg *new_cfg);
extern alert_status_t mpu6050_get_status(void);

extern void mpu6050_configure_ranges(enum mpu6050_range gyro_range,
		enum mpu6050_accel_range accel_range,
		enum mpu6050_filter filter_setting);

extern void mpu6050_exti_handler(EXTDriver *extp UNUSED, expchannel_t channel UNUSED);

#endif /* TASK_MPU6050_H */
