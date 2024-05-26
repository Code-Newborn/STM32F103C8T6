#ifndef __IR_REMOTE_H__
#define __IR_REMOTE_H__


#include <stdint.h>
#include "main.h"

uint8_t IR_HighLevelPeriod( void );

// 定义全局变量
extern uint32_t receive_Code;  // 定义一个32位数据变量，保存接收码
extern uint8_t  receive_Flag;  // 定义一个8位数据的变量，用于指示接收标志

#endif
