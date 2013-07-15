#ifndef ALERT_H
#define ALERT_H

#include "ch.h"
#include "hal.h"


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
#define debug(...)	chprintf(&SD2, ##__VA_ARGS__)

#define UNUSED		__attribute__((unused))

#endif /* ALERT_H */
