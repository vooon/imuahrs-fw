#ifndef TASK_SERVOPWM_H
#define TASK_SERVOPWM_H

#include "hal.h"

struct servopwm_channel {
	struct PWMDriver *pwmdp;
	uint16_t channel;
};

struct servopwm_cfg {
	const struct servopwm_channel *channels;
	size_t channels_count;
	uint16_t pulse_min;
	uint16_t pulse_max;
};

extern void servopwm_init(const struct servopwm_cfg *cfg);
extern void servopwm_set_channel(uint8_t channel, uint16_t pulse);

#endif /* TASK_SERVOPWM_H */
