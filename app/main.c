/**
 * IMU AHRS sensor board firmware
 *
 * @author Vladimir Ermakov Copyright (C) 2013.
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

#include <stdint.h>
#include <stdbool.h>

#include "ch.h"
#include "hal.h"

#include "app_config.h"
#include "led.h"
#include "alert.h"
#include "protocol.h"
#include "task_bmp085.h"
#include "task_ms5611.h"
#include "task_mpu6050.h"
#include "task_hmc5883.h"
#include "task_servopwm.h"

EVENTSOURCE_DECL(alert_event_source);

enum led_status {
	LST_INIT,
	LST_FAIL,
	LST_NORMAL
};

#ifdef LED_PWM

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

#else

void led_update(enum led_status ls)
{
	if (ls == LST_FAIL) {
		LED_FAIL_TOGGLE();
		LED_OFF();
		LED_NORMAL_OFF();
	}
	else if (ls == LST_NORMAL) {
		LED_TOGGLE();
		LED_NORMAL_ON();
		LED_FAIL_OFF();
	}
	else { /* INIT */
		LED_TOGGLE();
		LED_NORMAL_OFF();
		LED_FAIL_OFF();
	}
}

#endif /* LED_PWM */

/*
 * HW config
 */

#ifdef BOARD_IMU_AHRF

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

static const EXTConfig extcfg = {
	{
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL}, /* PA4 - BMP085 EOC (nc) */
		{EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOA, hmc5883_exti_handler}, /* PA5 - HMC5883 DRDY */
		{EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOA, mpu6050_exti_handler}, /* PA6 - MPU6050 IRQ */
		{EXT_CH_MODE_DISABLED, NULL}, /* PA7 - MPU6050 FSYNC */
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
	}
};

#endif /* BOARD_IMU_AHRF */

#ifdef BOARD_CAPTAIN_PRO2

static const PWMConfig pwm3cfg = {
	1000000,
	20000,
	NULL,
	{
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* PWMO5 */
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* PWMO6 */
		{PWM_OUTPUT_DISABLED, NULL},
		{PWM_OUTPUT_DISABLED, NULL}
	},
	0, 0
};

static const PWMConfig pwm4cfg = {
	1000000,
	20000,
	NULL,
	{
		{PWM_OUTPUT_DISABLED, NULL},
		{PWM_OUTPUT_DISABLED, NULL},
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* PWMO7 */
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}  /* PWMO8 */
	},
	0, 0
};

static const PWMConfig pwm5cfg = {
	1000000,
	20000,
	NULL,
	{
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* PWMO4 */
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* PWMO3 */
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* PWMO2 */
		{PWM_OUTPUT_ACTIVE_HIGH, NULL}, /* PWMO1 */
	},
	0, 0
};

static const I2CConfig i2c1cfg = {
	OPMODE_I2C,
	400000,
	FAST_DUTY_CYCLE_2
};

static const EXTConfig extcfg = {
	{
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, hmc5883_exti_handler}, /* PC8 - HMC5883 DRDY */
		{EXT_CH_MODE_RISING_EDGE | EXT_CH_MODE_AUTOSTART | EXT_MODE_GPIOC, mpu6050_exti_handler}, /* PC9 - MPU6050 IRQ */
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
		{EXT_CH_MODE_DISABLED, NULL},
	}
};

static const struct servopwm_channel servo_channels[] = {
	{ &PWMD5, 3 },
	{ &PWMD5, 2 },
	{ &PWMD5, 1 },
	{ &PWMD5, 0 },
	{ &PWMD3, 0 },
	{ &PWMD3, 1 },
	{ &PWMD4, 2 },
	{ &PWMD4, 3 },
};

static const struct servopwm_cfg servopwmcfg = {
	.channels = servo_channels,
	.channels_count = 8,
	.pulse_min = 800,
	.pulse_max = 2500,
};

#endif /* BOARD_CAPTAIN_PRO2 */

static const struct mpu6050_cfg mpu6050cfg = {
	.Fifo_store = MPU6050_FIFO_TEMP_OUT | MPU6050_ACCEL_OUT |
		MPU6050_FIFO_GYRO_X_OUT | MPU6050_FIFO_GYRO_Y_OUT | MPU6050_FIFO_GYRO_Z_OUT,
	.Smpl_rate_div_no_dlp = 11, /* Clock at 8 kHz, downsampled by 12 for 666 Hz */
	.Smpl_rate_div_dlp = 1,     /* with dlp on output rate is 500 Hz */
	.interrupt_cfg = MPU6050_INT_CLR_ANYRD | MPU6050_INT_I2C_BAYPASS_EN,
	.interrupt_en = MPU6050_INTEN_DATA_RDY,
	.User_ctl = /*MPU6050_USERCTL_FIFO_EN*/ 0,
	.Pwr_mgmt_clk = MPU6050_PWRMGMT_PLL_X_CLK,
	.accel_range = MPU6050_ACCEL_8G,
	.gyro_range = MPU6050_SCALE_2000_DEG,
	.filter = MPU6050_LOWPASS_256_HZ,
	.orientation = MPU6050_TOP_0DEG
};

static const struct hmc5883_cfg hmc5883cfg = {
	.M_ODR = HMC5883_ODR_75,
	.Meas_Conf = HMC5883_MEASCONF_NORMAL,
	.Gain = HMC5883_GAIN_1_9,
	.Mode = HMC5883_MODE_CONTINUOUS

};

static const struct ms5611_cfg ms5611cfg = {
	.oversampling = MS5611_OSR_4096
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

#ifdef BOARD_IMU_AHRF
	/* Clear DRDY pad */
	palClearPad(GPIOA, GPIOA_DRDY);

	/* Activates serial */
	sdStart(&SD1, NULL);
	sdStart(&SD2, NULL);

	/* Activate pwm */
	pwmStart(&PWMD1, &pwm1cfg);

	/* Activate i2c */
	i2cStart(&I2CD1, &i2c1cfg);

	/* Activate exti */
	extStart(&EXTD1, &extcfg);

#endif /* BOARD_IMU_AHRF */
#ifdef BOARD_CAPTAIN_PRO2

	/* Activates serial */
	sdStart(&SD3, NULL);
	sdStart(&SD4, NULL);

	/* Activate pwm */
	pwmStart(&PWMD3, &pwm3cfg);
	pwmStart(&PWMD4, &pwm4cfg);
	pwmStart(&PWMD5, &pwm5cfg);

	/* Activate i2c */
	i2cStart(&I2CD1, &i2c1cfg);

	/* Activate exti */
	extStart(&EXTD1, &extcfg);

#endif /* BOARD_CAPTAIN_PRO2 */

	/* alert subsys */
	chEvtInit(&alert_event_source);
	chEvtRegister(&alert_event_source, &el0, 0);

	/* init devices */
	pt_init();
#ifdef HAS_DEV_BMP085
	bmp085_init();
#endif
#ifdef HAS_DEV_MS5611
	ms5611_init(&ms5611cfg);
#endif
#ifdef HAS_DEV_MPU6050
	mpu6050_init(&mpu6050cfg);
	chThdSleepMilliseconds(250); /* give some time for mpu6050 configuration */
#endif
#ifdef HAS_DEV_HMC5883
	hmc5883_init(&hmc5883cfg);
#endif
#ifdef HAS_DEV_SERVOPWM
	servopwm_init(&servopwmcfg);
#endif

#ifdef BOARD_IMU_AHRF
	/* Set DRDY pad */
	palSetPad(GPIOA, GPIOA_DRDY);
#endif

	while (TRUE) {
		eventmask_t msk = chEvtWaitOneTimeout(ALL_EVENTS, MS2ST(100));

		if (msk & EVENT_MASK(0)) {
			flagsmask_t fl = chEvtGetAndClearFlags(&el0);

			if (fl & ALERT_FLAG_PROTO)
				proto_st = pt_get_status();

#ifdef HAS_DEV_MPU6050
			if (fl & ALERT_FLAG_MPU6050)
				mpu6050_st = mpu6050_get_status();
#endif

#ifdef HAS_DEV_HMC5883
			if (fl & ALERT_FLAG_HMC5883)
				hmc5883_st = hmc5883_get_status();
#endif

#ifdef HAS_DEV_BMP085
			if (fl & ALERT_FLAG_BMP085)
				bmp085_st = bmp085_get_status();
#endif

#ifdef HAS_DEV_MS5611
			if (fl & ALERT_FLAG_BMP085)
				bmp085_st = ms5611_get_status();
#endif

			pt_set_sens_state(mpu6050_st, hmc5883_st, bmp085_st);
		}

		if (proto_st == ALST_FAIL || mpu6050_st == ALST_FAIL || hmc5883_st == ALST_FAIL || bmp085_st == ALST_FAIL)
			lstat = LST_FAIL;
		else if (proto_st == ALST_INIT || mpu6050_st == ALST_INIT || hmc5883_st == ALST_INIT || bmp085_st == ALST_INIT)
			lstat = LST_INIT;
		else if (proto_st == ALST_NORMAL && mpu6050_st == ALST_NORMAL && hmc5883_st == ALST_NORMAL && bmp085_st == ALST_NORMAL)
			lstat = LST_NORMAL;

		led_update(lstat);
	}
}

