#ifndef LED_H
#define LED_H

#include "hal.h"

#define LED_ON()		palClearPad(GPIOA, GPIOA_LED)
#define LED_OFF()		palSetPad(GPIOA, GPIOA_LED)
#define LED_TOGGLE()		palTogglePad(GPIOA, GPIOA_LED)

#define LED_ENABLE_PWM_MODE()	palSetPadMode(GPIOA, GPIOA_LED, PAL_MODE_STM32_ALTERNATE_PUSHPULL)
#define LED_DISABLE_PWM_MODE()	palSetPadMode(GPIOA, GPIOA_LED, PAL_MODE_OUTPUT_PUSHPULL)

#define LED_PWM(newpw)		pwmEnableChannel(&PWMD1, 0, (newpw));

#endif /* LED_H */
