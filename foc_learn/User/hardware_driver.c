#include "hardware_driver.h"
#include "tim.h"

void motor_hardware_init(void)
{
    motor_pwm_enable();
    HAL_TIM_Base_Start_IT(&htim6);

}

void motor_pwm_enable(void)
{
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_2);
    HAL_TIM_PWM_Start(&htim1,TIM_CHANNEL_3);
    HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Start(&htim1,TIM_CHANNEL_3);
}

void motor_pwm_disable(void)
{
    HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_1);
    HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_2);
    HAL_TIM_PWM_Stop(&htim1,TIM_CHANNEL_3);
    HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_1);
    HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_2);
    HAL_TIMEx_PWMN_Stop(&htim1,TIM_CHANNEL_3);
}

void motor_set_pwm(uint16_t Tcmp1, uint16_t Tcmp2, uint16_t Tcmp3)
{
    /* 计算出的三项CCR比较值 赋值给三路CCR比较值寄存器 */
    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_1,Tcmp1);
    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_2,Tcmp2);
    __HAL_TIM_SetCompare(&htim1,TIM_CHANNEL_3,Tcmp3);
}


