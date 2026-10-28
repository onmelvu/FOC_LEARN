#include "encoder.h"

void encoder_param_init(encoder_typedef *state, uint32_t line, uint8_t dir)
{
    state->line = line;
    state->dir = dir;
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

    state->theta = state->pulse_data / (float)state->line * _2PI;
}

