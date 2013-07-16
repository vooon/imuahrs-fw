/**
 ******************************************************************************
 * @file       pios_hmc5883.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2012.
 * @brief      HMC5883 functions header.
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

#ifndef TASK_HMC5883_H
#define TASK_HMC5883_H

#include "hal.h"
#include "alert.h"

/* Output Data Rate */
#define HMC5883_ODR_0_75           0x00
#define HMC5883_ODR_1_5            0x04
#define HMC5883_ODR_3              0x08
#define HMC5883_ODR_7_5            0x0C
#define HMC5883_ODR_15             0x10
#define HMC5883_ODR_30             0x14
#define HMC5883_ODR_75             0x18

/* Measure configuration */
#define HMC5883_MEASCONF_NORMAL    0x00
#define HMC5883_MEASCONF_BIAS_POS  0x01
#define HMC5883_MEASCONF_BIAS_NEG  0x02

/* Gain settings */
#define HMC5883_GAIN_0_88          0x00
#define HMC5883_GAIN_1_3           0x20
#define HMC5883_GAIN_1_9           0x40
#define HMC5883_GAIN_2_5           0x60
#define HMC5883_GAIN_4_0           0x80
#define HMC5883_GAIN_4_7           0xA0
#define HMC5883_GAIN_5_6           0xC0
#define HMC5883_GAIN_8_1           0xE0

/* Modes */
#define HMC5883_MODE_CONTINUOUS    0x00
#define HMC5883_MODE_SINGLE        0x01
#define HMC5883_MODE_IDLE          0x02
#define HMC5883_MODE_SLEEP         0x03

struct hmc5883_cfg {
    uint8_t M_ODR; /* OUTPUT DATA RATE --> here below the relative define (See datasheet page 11 for more details) */
    uint8_t Meas_Conf; /* Measurement Configuration,: Normal, positive bias, or negative bias --> here below the relative define */
    uint8_t Gain; /* Gain Configuration, select the full scale --> here below the relative define (See datasheet page 11 for more details) */
    uint8_t Mode;
};

/* Public Functions */
extern void hmc5883_init(const struct hmc5883_cfg *new_cfg);
extern alert_status_t hmc5883_get_status(void);

extern void hmc5883_exti_handler(EXTDriver *extp UNUSED, expchannel_t channel UNUSED);

#endif /* TASK_MPU6050_H */
