#include "motor_machie.h"
#include "board_config.h"

motor_typedef motor_system;

void motor_state_machie_init(motor_typedef *state)
{
    motor_hardware_init();
    /* 设置电机母线和pwm周期 */
    set_udc_tpwm_param(&state->foc, UDC, TPWM);
    vf_speed_control_param_init(&state->vf, ACC, TARGET_SPEED, DEAD_ZONE, FOC_TS);

    /* 初始化编码器 */
    encoder_param_init(&state->encoder, ENCODER_LINE, 0, MOTOR_PN, 2572);
}

void motor_state_machie_run(motor_typedef *state)
{
    uint16_t data = 0;
    data = mt6701_read_data();
    encoder_update(&state->encoder, data);

    switch (state->theta_mode)
    {
        /* 定位状态 0 */
        case THETA_MODE_ZERO:
            state->foc.Theta = 0;
            break;
            /* VF角度自增状态 */
        case THETA_MODE_VF:
            vf_speed_control_update(&state->vf, &state->foc.Theta);
            break;
            /* 编码器 */
        case THETA_MODE_ENCODER:
            state->foc.Theta = state->encoder.theta_e;
            break;    
        default:
            break;
    }

    /* foc 角度 */
    // vf_speed_control_update(&state->vf, &state->foc.Theta);

    // state->foc.Theta = state->encoder.theta_e;

    /* 设置参数 */
    // state->foc.Vd = 0;
    // state->foc.Vq = 0.3f;

    foc_voltage_update(&state->foc);

    motor_set_pwm(state->foc.Tcmp1, state->foc.Tcmp2, state->foc.Tcmp3);
}
