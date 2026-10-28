#ifndef __HARDWARE_DRIVER_H__
#define __HARDWARE_DRIVER_H__

#include "stdint.h"

void motor_hardware_init(void);
void motor_pwm_enable(void);
void motor_pwm_disable(void);
void motor_set_pwm(uint16_t Tcmp1, uint16_t Tcmp2, uint16_t Tcmp3);

uint16_t mt6701_read_data(void);

#endif
