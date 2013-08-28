#ifndef TASK_RPM
#define TASK_RPM

#include "hal.h"
#include "alert.h"

extern void rpm_init(void);
extern void rpm_stop_engine(bool en);

extern void rpm_exti_handler(EXTDriver *extp UNUSED, expchannel_t channel UNUSED);

#endif /* TASK_RPM */
