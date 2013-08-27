/**
 * @file       protocol.h
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

#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "alert.h"

#define FW_VERSION "0.2.0"

enum pt_msgid {
	ID_VERSION = 0x00,
	ID_SENS_TEST = 0x01,
	ID_HEARTBEAT = 0x02,
	ID_SERVO_SET = 0x03,
	ID_MESG_EN = 0xc0,
	ID_MPU_CFG = 0xc1,
	ID_HMC_CFG = 0xc2,
	ID_BMP_CFG = 0xc3,
	ID_MPU_DAT = 0xd0,
	ID_MAG_DAT = 0xd1,
	ID_BAR_DAT = 0xd2,
	ID_TRM_DAT = 0xd3
};

struct pt_mpu_dat {
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	int16_t temperature;
} PACK_STRUCT_STRUCT;

struct pt_mag_dat {
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;
} PACK_STRUCT_STRUCT;

struct pt_bar_dat {
	int32_t pressure;
	int16_t temperature;
} PACK_STRUCT_STRUCT;

struct pt_servo_set {
	uint8_t channel;
	uint16_t pulse;
} PACK_STRUCT_STRUCT;

struct pt_trm_dat {
	int16_t temperature;
} PACK_STRUCT_STRUCT;

extern void pt_init(void); /* start main receiver thread */
extern alert_status_t pt_get_status(void);

extern void pt_set_sens_state(alert_status_t mpu, alert_status_t hmc, alert_status_t bmp);
extern void pt_send_mpu_dat(int16_t gx, int16_t gy, int16_t gz, int16_t ax, int16_t ay, int16_t az, int16_t temp);
extern void pt_send_mag_dat(int16_t mag_x, int16_t mag_y, int16_t mag_z);
extern void pt_send_bar_dat(int32_t pressure, int16_t temperature);
extern void pt_send_trm_dat(int16_t temperature);

#endif /* PROTOCOL_H */
