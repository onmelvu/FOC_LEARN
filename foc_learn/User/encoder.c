#include "encoder.h"
#include "math.h"

void encoder_param_init(encoder_typedef *state, uint32_t line, uint8_t dir, uint8_t motor_pn, uint32_t pulse)
{
    state->line = line;
    state->dir = dir;
    state->motor_pn = motor_pn;
    state->pulse = pulse;
}

void encoder_update(encoder_typedef *state, uint32_t data)
{
    if(state->dir == 0)
    {
        state->pulse_data = data;
    }
    else
    {
        state->pulse_data = state->line - data;
    }

    /* 计算误差 */
    uint32_t temp = (state->pulse_data - state->pulse + state->line) % state->line;
    /* 计算机械角度 */
    state->theta = (float)temp / (float)state->line * _2PI;
    /* 计算电角度 = 极对数 * 机械角度 */
    state->theta_e = fmod(state->motor_pn * state->theta, _2PI);
}

