#include "motor_machie.h"
#include "board_config.h"

motor_typedef motor_system;

void motor_state_machie_init(motor_typedef *state)
{
    motor_hardware_init();
    /* 设置电机母线和pwm周期 */
    set_udc_tpwm_param(&state->foc, UDC, TPWM);
    vf_speed_control_param_init(&state->vf, ACC, TARGET_SPEED, DEAD_ZONE, FOC_TS);
}

void motor_state_machie_run(motor_typedef *state)
{
    /* foc 角度 */
    vf_speed_control_update(&state->vf, &state->foc.Theta);

    /* 设置参数 */
    state->foc.Vd = 0;
    state->foc.Vq = 0.3f;

    foc_voltage_update(&state->foc);

    motor_set_pwm(state->foc.Tcmp1, state->foc.Tcmp2, state->foc.Tcmp3);
}
