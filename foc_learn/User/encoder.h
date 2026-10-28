#ifndef __ENCODER_H__
#define __ENCODER_H__
#include "stdint.h"

#define _2PI        6.283185307179f

typedef struct
{
    uint32_t    line;           /* 编码器线数 */
    uint8_t     dir;            /* 编码器方向 */
    uint32_t    pulse_data;     /* 原始数据 */
    float       theta;          /* 机械角度 */
}encoder_typedef;

void encoder_param_init(encoder_typedef *state, uint32_t line, uint8_t dir);
void encoder_update(encoder_typedef *state, uint32_t data);
#endif
