#ifndef ALERT_H
#define ALERT_H

#include "ch.h"
#include "hal.h"
#include <stdint.h>
#include <stdbool.h>


typedef enum {
	ALST_INIT = 0,
	ALST_FAIL,
	ALST_NORMAL
} alert_status_t;


extern EventSource alert_event_source;

#define ALERT_BMP085	EVENT_MASK(4)
#define ALERT_HMC5883	EVENT_MASK(5)
#define ALERT_MPU6050	EVENT_MASK(6)


#define _ALERT_SET(newst, module, alst)						\
do {										\
	alert_status_t tmp = alst;						\
	alst = newst;								\
	if (tmp != newst)							\
		chEvtBroadcastFlags(&alert_event_source, ALERT_ ## module);	\
} while(0)


#define ALERT_SET_FAIL(module, alst)	\
	_ALERT_SET(ALST_FAIL, module, alst)

#define ALERT_SET_NORMAL(module, alst)	\
	_ALERT_SET(ALST_NORMAL, module, alst)


#include "chprintf.h"
#define debug(...) chprintf(&SD2, ##__VA_ARGS__)

#endif /* ALERT_H */
