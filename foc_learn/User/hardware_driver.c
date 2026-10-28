#include "hardware_driver.h"
#include "tim.h"
#include "spi.h"

void motor_hardware_init(void)
{
    /*  */
    HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_4);
    __HAL_TIM_ENABLE_IT(&htim1, TIM_IT_CC4);
    motor_pwm_enable();
    
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

uint16_t mt6701_read_data(void)
{
    uint8_t rx[3] = {0};
    uint8_t tx[3] = {0};

    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET);
    HAL_SPI_TransmitReceive(&hspi1, tx, rx, 3, 0xffffff);
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET);
    return ((rx[0] << 6) | (rx[1] >> 2)) & 0x3FFF;
}
