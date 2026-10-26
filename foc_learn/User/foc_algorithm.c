#include "foc_algorithm.h"
#include "tim.h"


/**
 * @brief 反park变换
 */
void rev_park_transf(foc_typedef *state)
{
    state->Valpha = state->Vd * cosf(state->Theta) - state->Vq * sinf(state->Theta);
    state->Vbeta  = state->Vd * sinf(state->Theta) + state->Vq * cosf(state->Theta);
}

/**
 * @brief 反clark变换
 */
void rev_clark_transf(foc_typedef *state)
{
    state->Vu = state->Valpha;
    state->Vv = -0.5f * state->Valpha + 0.8660254f * state->Vbeta;
    state->Vw = -0.5f * state->Valpha - 0.8660254f * state->Vbeta;
}

/**
 * @brief svpwm 零序分量注入
 */
void svpwm_zero_sq_inject(foc_typedef *state)
{
    float max = (state->Vu > state->Vv) ? (state->Vu > state->Vw ? state->Vu : state->Vw) : (state->Vv > state->Vw ? state->Vv : state->Vw);
    float min = (state->Vu < state->Vv) ? (state->Vu < state->Vw ? state->Vu : state->Vw) : (state->Vv < state->Vw ? state->Vv : state->Vw);

    float v0  = -0.5f * (min + max);

    /* 计算三相马鞍波电压 */
    state->Vu_Mod = v0 + state->Vu;
    state->Vv_Mod = v0 + state->Vv;
    state->Vw_Mod = v0 + state->Vw;

    /* 转换为三相pwm比较值 */
    state->Tcmp1 = (state->Vu_Mod / state->Udc +0.5f) * state->Tpwm;
    state->Tcmp2 = (state->Vv_Mod / state->Udc +0.5f) * state->Tpwm;
    state->Tcmp3 = (state->Vw_Mod / state->Udc +0.5f) * state->Tpwm;

    
}

void set_udc_tpwm_param(foc_typedef *foc, float udc, float tpwm)
{
    foc->Udc    = udc;
    foc->Tpwm   = tpwm;
}

/* 坐标变换电压更新函数 */
void foc_voltage_update(foc_typedef *state)
{
    /* 反park变换 */
  rev_park_transf(state);

  /* 反clark变换 */
  rev_clark_transf(state);

  /* svpwm 零序分量注入 */
  svpwm_zero_sq_inject(state);
}

/* vf速度控制参数初始化 */
void vf_speed_control_param_init(vf_typedef *state, float acc, float target_speed, float dead_zone, float ts)
{
    state->acc = acc;
    state->target_speed = target_speed;
    state->dead_zone = dead_zone;
    state->ts = ts;
}

void vf_speed_control_update(vf_typedef *state, float *target_theta_add)
{
    state->speed_error = state->target_speed - state->speed_integrator;

    /* 死区处理 */
    if(fabs(state->speed_error) < state->dead_zone)
    {
        state->speed_error_dead = 0;
    }
    else
    {
        state->speed_error_dead = state->speed_error;
    }

    /* 加速度方向 */
    if(state->speed_error_dead > 0)
    {
        state->acc_dir = 1;
    }
    else if(state->speed_error_dead < 0)
    {
        state->acc_dir = -1;
    }
    else
    {
        state->acc_dir = 0;
    }

    /* 加速度积分得到速度 */
    state->speed_integrator += state->acc_dir * state->acc * state->ts;

    /* 速度积分得到角度 */
    state->theta_integrator += state->speed * state->ts;
    /* 输出角度 */
    state->theta = fmod(state->theta_integrator, _2PI);

    if(state->theta < 0)
    {
        state->theta += _2PI;
    }

    /* 输出速度 */
    state->speed = state->speed_integrator;

    /* 指针传参 */
    *target_theta_add = state->theta;
}
