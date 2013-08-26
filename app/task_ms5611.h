/**
 ******************************************************************************
 * @file       pios_ms5611.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2010.
 * @brief      BMP085 functions header.
 * @see        The GNU Public License (GPL) Version 3
 *
 *****************************************************************************/
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

#ifndef TASK_MS5611_H
#define TASK_MS5611_H

#include "hal.h"
#include "alert.h"

struct ms5611_cfg {
    uint32_t oversampling;
};

enum ms5611_osr {
    MS5611_OSR_256  = 0,
    MS5611_OSR_512  = 2,
    MS5611_OSR_1024 = 4,
    MS5611_OSR_2048 = 6,
    MS5611_OSR_4096 = 8,
};

/* Public Functions */
extern void ms5611_init(const struct ms5611_cfg *cfg);
extern alert_status_t ms5611_get_status(void);
static inline void ms5611_reconfigure(void) {  }; /* stub reconfiguration for sensor */

#endif /* TASK_BMP085_H */
