#ifndef _APP_CONFIG_H_
#define _APP_CONFIG_H_

#define HAS_DEV_MPU6050
#define HAS_DEV_HMC5883
#define HAS_DEV_MS5611
#define HAS_DEV_SERVOPWM
#define HAS_DEV_NTC10K
#define HAS_DEV_RPM

#define PROTO_SD SD4
#define SHELL_SD SD3

#define NTC10K_GPIO GPIOC
#define NTC10K_PIN  5

#define RPM_SIG_GPIO GPIOC
#define RPM_KILL_GPIO GPIOC
#define RPM_SIG_PIN  4
//#define RPM_KILL_PIN  4
#define RPM_KILL_PIN  3

#endif /* _APP_CONFIG_H_ */
