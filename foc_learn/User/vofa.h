#ifndef __VOFA_H__
#define __VOFA_H__

#include "stdint.h"
#include "string.h"
#include "usbd_cdc_if.h"

#define data_num    9                   //发送数量
#define data_len    (data_num * 4 + 4)  // 发送长度
typedef struct vofa
{
    float   send_data_array[data_num];
    uint8_t byte_data_array[data_len];
}vofa_send_t;

extern vofa_send_t vofa_send;

void vofa_send_task(void);
void vofa_data_process(void);



#endif
