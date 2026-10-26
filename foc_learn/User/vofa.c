#include "vofa.h"
#include "motor_machie.h"

vofa_send_t vofa_send;

/* vofa 发送任务 */
void vofa_send_task(void)
{
    /* 临时添加模拟数据 */
    vofa_send.send_data_array[0] = motor_system.foc.Theta;
    vofa_send.send_data_array[1] = motor_system.vf.theta;
    vofa_send.send_data_array[2] = motor_system.vf.speed;
    vofa_send.send_data_array[3] = motor_system.vf.target_speed;
    vofa_send.send_data_array[4] = motor_system.foc.Vv;
    vofa_send.send_data_array[5] = motor_system.foc.Vw;
    vofa_send.send_data_array[6] = motor_system.foc.Vu_Mod;
    vofa_send.send_data_array[7] = motor_system.foc.Vv_Mod;
    vofa_send.send_data_array[8] = motor_system.foc.Vw_Mod;

    vofa_data_process();
}

/* vofa 处理函数 */
void vofa_data_process(void)
{
    /* 通过拷贝将浮点数据转换成单字节数据 */
    memcpy(vofa_send.byte_data_array, vofa_send.send_data_array, data_len);
    vofa_send.byte_data_array[data_len - 4] = 0x00;
    vofa_send.byte_data_array[data_len - 3] = 0x00;
    vofa_send.byte_data_array[data_len - 2] = 0x80;
    vofa_send.byte_data_array[data_len - 1] = 0x7f;

    /* usb 发送数据 */
    CDC_Transmit_FS((uint8_t *)vofa_send.byte_data_array, data_len);
}
