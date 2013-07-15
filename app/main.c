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
#include "alert.h"
#include "task_bmp085.h"

EVENTSOURCE_DECL(alert_event_source);

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

static const PWMConfig pwm1cfg = {
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

static const I2CConfig i2c1cfg = {
	OPMODE_I2C,
	400000,
	FAST_DUTY_CYCLE_2
};

/*
 * Application entry point.
 */
int main(void)
{
	enum led_status lstat = LST_INIT;
	EventListener el0;
	alert_status_t proto_st = ALST_INIT;
	alert_status_t bmp085_st = ALST_INIT;
	alert_status_t mpu6050_st = ALST_INIT;
	alert_status_t hmc5883_st = ALST_INIT;

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

	/* Activate i2c */
	i2cStart(&I2CD1, &i2c1cfg);

	/* alart subsys */
	chEvtInit(&alert_event_source);
	chEvtRegister(&alert_event_source, &el0, 0);

	/* init devices */
	bmp085_init();

	chThdSleepMilliseconds(100);
	bmp085_st = bmp085_get_status();

	while (TRUE) {
		eventmask_t msk = chEvtWaitAllTimeout(ALL_EVENTS, MS2ST(100));

		if (msk & EVENT_MASK(0)) {
			flagsmask_t fl = chEvtGetAndClearFlags(&el0);

			debug("event flags: 0x%08x\n", fl);

			if (fl & ALERT_FLAG_BMP085)
				bmp085_st = bmp085_get_status();


			//mpu6050_st = mpu6050_get_status();
			//hmc5882_st = hmc5883_get_status();
			//proto_st = pr_get_status();
		}

		if (bmp085_st == ALST_INIT /* || mpu6050_st == ALST_INIT || hmc5883_st == ALST_INIT*/)
			lstat = LST_INIT;
		else if (bmp085_st == ALST_NORMAL /* && mpu6050_st == ALST_NORMAL && hmc5883_st == ALST_NORMAL*/)
			lstat = LST_NORMAL;
		else if (bmp085_st == ALST_FAIL /* || mpu6050_st == ALST_FAIL || hmc5883_st == ALST_FAIL*/)
			lstat = LST_FAIL;

		led_update(lstat);
	}
}
