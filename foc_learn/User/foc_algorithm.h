#ifndef __FOC_ALGORITHM_H__
#define __FOC_ALGORITHM_H__

#include "math.h"

#define _2PI        6.283185307179f

typedef struct
{
    float Udc;      /* 母线电压 */
    float Tpwm;     /* PWM周期 */
    float Vd;       /* d轴电压 */
    float Vq;       /* q轴电压 */
    float Theta;    /* 电机角度 */

    float Valpha;   /* alpha电压 */
    float Vbeta;    /* beta电压 */
    
    float Vu;       /* U相电压 */
    float Vv;       /* V相电压 */
    float Vw;       /* W相电压 */
    
    float Vu_Mod;   /* U相调制电压 */
    float Vv_Mod;   /* V相调制电压 */
    float Vw_Mod;   /* W相调制电压 */

    int Tcmp1;      /* U相的比较值 */
    int Tcmp2;      /* V相的比较值 */
    int Tcmp3;      /* W相的比较值 */

}foc_typedef;


/* vf角度生成器参数结构体 */
typedef struct 
{
    /* 输入参数 */
    float acc;          /* 加速度 */
    float target_speed; /* 目标速度 */
    float dead_zone;    /* 死区阈值 */
    float ts;           /* 步长 ---->  两次中断的间隔 */

    /* 中间参数 */
    float speed_error;      /* 速度误差 */
    float speed_error_dead; /* 带死区的速度误差 */
    float acc_dir;          /* 加速度方向 */
    float speed_integrator; /* 速度积分器 */
    float theta_integrator; /* 角度积分器 */

    /* 输出参数 */
    float speed;        /* 实际速度 */
    float theta;        /* 实际角度 */

}vf_typedef;



void rev_park_transf(foc_typedef *state);
void rev_clark_transf(foc_typedef *state);
void svpwm_zero_sq_inject(foc_typedef *state);
void foc_voltage_update(foc_typedef *state);
void set_udc_tpwm_param(foc_typedef *foc, float udc, float tpwm);
void vf_speed_control_param_init(vf_typedef *state, float acc, float target_speed, float dead_zone, float ts);
void vf_speed_control_update(vf_typedef *state, float *target_theta_add);

#endif
