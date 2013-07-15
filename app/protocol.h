#ifndef PROTOCOL_H
#define PROTOCOL_H

#include "alert.h"

enum pt_msgid {
	ID_VERSION = 0x00,
	ID_SENS_TEST = 0x01,
	ID_HEARTBEAT = 0x02,
	ID_MESG_EN = 0xc0,
	ID_MPU_CFG = 0xc1,
	ID_HMC_CFG = 0xc2,
	ID_BMP_CFG = 0xc3,
	ID_MPU_DAT = 0xd0,
	ID_MAG_DAT = 0xd1,
	ID_BAR_DAT = 0xd2
};

struct pt_mpu_dat {
	int16_t gyro_x;
	int16_t gyro_y;
	int16_t gyro_z;
	int16_t accel_x;
	int16_t accel_y;
	int16_t accel_z;
	int16_t temperature;
} PACK_STRUCT_STRUCT;

struct pt_mag_dat {
	int16_t mag_x;
	int16_t mag_y;
	int16_t mag_z;
} PACK_STRUCT_STRUCT;

struct pt_bar_dat {
	int32_t pressure;
	int16_t temperature;
} PACK_STRUCT_STRUCT;


extern void pt_init(void); /* start main receiver thread */
extern alert_status_t pt_get_status(void);

extern void pt_set_sens_state(alert_status_t mpu, alert_status_t hmc, alert_status_t bmp);
extern void pt_send_mpu_dat(int16_t gx, int16_t gy, int16_t gz, int16_t ax, int16_t ay, int16_t az, int16_t temp);
extern void pt_send_mag_dat(int16_t mag_x, int16_t mag_y, int16_t mag_z);
extern void pt_send_bar_dat(int32_t pressure, int16_t temperature);

#endif /* PROTOCOL_H */
