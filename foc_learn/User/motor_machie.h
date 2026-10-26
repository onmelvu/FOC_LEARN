#ifndef __MOTOR_MACHIE_H__
#define __MOTOR_MACHIE_H__

#include "foc_algorithm.h"
#include "hardware_driver.h"
#include "board_config.h"

typedef struct
{
    foc_typedef foc;
    vf_typedef vf;
}motor_typedef;

extern motor_typedef motor_system;;

void motor_state_machie_init(motor_typedef *state);
void motor_state_machie_run(motor_typedef *state);

#endif
