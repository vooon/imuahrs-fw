/*
    ChibiOS/RT - Copyright (C) 2006-2013 Giovanni Di Sirio

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include <stdint.h>
#include <stdbool.h>

#include "ch.h"
#include "hal.h"

#include "led.h"

enum led_status {
	LST_INIT,
	LST_FAIL,
	LST_NORMAL
};

void led_update(enum led_status ls)
{
	static bool is_pwm = false;
	static bool step_sign = false;
	static const int pwm_max = 100;
	static const int pwm_one_step = 10;
	static int pwm_last = 0;

	if (!is_pwm && ls == LST_NORMAL) {
		LED_ENABLE_PWM_MODE();
		is_pwm = true;
	}
	else if (is_pwm && ls != LST_NORMAL) {
		LED_DISABLE_PWM_MODE();
		is_pwm = false;
	}

	if (ls == LST_FAIL) {
		LED_ON();
	}
	else if (ls == LST_NORMAL) {
		pwm_last += (step_sign) ? -pwm_one_step : pwm_one_step;
		if (0 > pwm_last || pwm_last > pwm_max) {
			step_sign = !step_sign;
			pwm_last += (step_sign) ? -pwm_one_step : pwm_one_step;
		}

		LED_PWM(pwm_last);
	}
	else { /* INIT */
		LED_TOGGLE();
	}
}

/*
 * HW config
 */

static PWMConfig pwm1cfg = {
	1000,
	100,
	NULL,
	{
		{PWM_OUTPUT_ACTIVE_LOW, NULL}, /* LED */
		{PWM_OUTPUT_DISABLED, NULL},
		{PWM_OUTPUT_DISABLED, NULL},
		{PWM_OUTPUT_DISABLED, NULL}
	},
	0
};

/*
 * Application entry point.
 */
int main(void)
{

	enum led_status ls;

	/*
	 * System initializations.
	 * - HAL initialization, this also initializes the configured device drivers
	 *   and performs the board-specific initializations.
	 * - Kernel initialization, the main() function becomes a thread and the
	 *   RTOS is active.
	 */
	halInit();
	chSysInit();

	/* Activates serial */
	sdStart(&SD1, NULL);
	sdStart(&SD2, NULL);

	/* Activate pwm */
	pwmStart(&PWMD1, &pwm1cfg);

	/*
	 * Creates the blinker thread.
	 */
	//chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

	int i = 0;
	ls = LST_INIT;
	while (TRUE) {
		chThdSleepMilliseconds(50);

		if (i < 100)
			ls = LST_INIT;
		else if (i < 200)
			ls = LST_FAIL;
		else
			ls = LST_NORMAL;

		led_update(ls);

		if (++i > 1000)
			i = 0;
	}
}
