
#include "task_servopwm.h"

const struct servopwm_cfg *dev_cfg;

void servopwm_init(const struct servopwm_cfg *cfg)
{
	dev_cfg = cfg;
}

void servopwm_set_channel(uint8_t channel, uint16_t pulse)
{
	if (!dev_cfg || channel >= dev_cfg->channels_count)
		return;

	struct servopwm_channel *chan = dev_cfg->channels + channel;

	if (pulse == 0) {
		pwmDisableChannel(chan->pwmdp, chan->channel);
	}
	else {
		if (pulse < dev_cfg->pulse_min)
			pulse = dev_cfg->pulse_min;
		else if (pulse > dev_cfg->pulse_max)
			pulse = dev_cfg->pulse_max;

		pwmEnableChannel(chan->pwmdp, chan->channel, pulse);
	}
}

