/**
 * @file       alert.h
 * @brief      Alert LED/State functions
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

#ifndef ALERT_H
#define ALERT_H

#include "ch.h"
#include "hal.h"

#include "app_config.h"

typedef enum {
	ALST_INIT = 0,
	ALST_FAIL,
	ALST_NORMAL
} alert_status_t;


extern EventSource alert_event_source;

#define ALERT_FLAG_BMP085	1024
#define ALERT_FLAG_HMC5883	2048
#define ALERT_FLAG_MPU6050	4096
#define ALERT_FLAG_PROTO	8192

#define _ALERT_SET(newst, module, alst)							\
do {											\
	alert_status_t tmp = alst;							\
	alst = newst;									\
	if (tmp != newst)								\
		chEvtBroadcastFlags(&alert_event_source, ALERT_FLAG_ ## module);	\
} while(0)


#define ALERT_SET_INIT(module, alst)	\
	_ALERT_SET(ALST_INIT, module, alst)

#define ALERT_SET_FAIL(module, alst)	\
	_ALERT_SET(ALST_FAIL, module, alst)

#define ALERT_SET_NORMAL(module, alst)	\
	_ALERT_SET(ALST_NORMAL, module, alst)


#include "chprintf.h"
#define debug(...)	chprintf((BaseSequentialStream *)&SHELL_SD, ##__VA_ARGS__)

#define UNUSED		__attribute__((unused))

#endif /* ALERT_H */
