#ifndef __BOARD_CONFIG_H__
#define __BOARD_CONFIG_H__

/* 系统时序变量 */
#define FOC_HZ          20000  // 20kHz 的中断频率
#define ACC             50.0f
#define TARGET_SPEED    200.0f
#define DEAD_ZONE       0.0001f
#define FOC_TS          0.00005 // (1 / (float)(FOC_HZ))


#define _2PI    6.283185307179f

#define UDC     24.0f
#define TPWM    4249.0f

#define ENCODER_LINE    16383

#endif
