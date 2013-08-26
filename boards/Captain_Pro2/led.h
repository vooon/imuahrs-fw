#ifndef LED_H
#define LED_H

#include "hal.h"

#define LED_ON()		palClearPad(GPIOB, GPIOB_LED_B)
#define LED_OFF()		palSetPad(GPIOB, GPIOB_LED_B)
#define LED_TOGGLE()		palTogglePad(GPIOB, GPIOB_LED_B)

#define LED_NORMAL_ON()		palClearPad(GPIOB, GPIOB_LED_C)
#define LED_NORMAL_OFF()	palSetPad(GPIOB, GPIOB_LED_C)
#define LED_NORMAL_TOGGLE()	palTogglePad(GPIOB, GPIOB_LED_C)

#define LED_FAIL_ON()		palClearPad(GPIOB, GPIOB_LED_A)
#define LED_FAIL_OFF()		palSetPad(GPIOB, GPIOB_LED_A)
#define LED_FAIL_TOGGLE()	palTogglePad(GPIOB, GPIOB_LED_A)

#endif /* LED_H */
