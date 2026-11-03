#ifndef __MOTOR_MACHIE_H__
#define __MOTOR_MACHIE_H__

#include "foc_algorithm.h"
#include "hardware_driver.h"
#include "board_config.h"
#include "encoder.h"

typedef enum
{
    THETA_MODE_ZERO = 0,    /* 固定零度  （定位） */
    THETA_MODE_VF,          /* VF角度自增 */
    THETA_MODE_ENCODER,     /* 编码器角度 */
}motor_theta_mode_enum;


typedef struct
{
    motor_theta_mode_enum   theta_mode;
    foc_typedef             foc;
    vf_typedef              vf;
    encoder_typedef         encoder;
}motor_typedef;

extern motor_typedef motor_system;;

void motor_state_machie_init(motor_typedef *state);
void motor_state_machie_run(motor_typedef *state);

#endif
