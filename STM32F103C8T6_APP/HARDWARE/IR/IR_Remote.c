#include "IR_Remote.h"
#include "tim.h"

uint32_t receive_Code;  // 定义一个32位数据变量，保存接收码
uint8_t  receive_Flag;  // 定义一个8位数据的变量，用于指示接收标志

/*高电平持续时间函数*/
uint8_t IR_HighLevelPeriod( void ) {
    uint8_t t = 0;
    while ( HAL_GPIO_ReadPin( IR_remote_GPIO_Port, IR_remote_Pin ) == 1 ) {  // 高电平
        t++;
        delay_us( 20 );
        if ( t >= 250 )
            return t;  // 超时溢出
    }
    return t;
}
/*红外遥控外部中断回调函数*/
// 在中断回调函数中完成红外解码
void HAL_GPIO_EXTI_Callback( uint16_t GPIO_Pin ) {
    uint8_t Tim = 0, Ok = 0, Data, Num = 0;
    while ( 1 ) {
        if ( HAL_GPIO_ReadPin( IR_remote_GPIO_Port, IR_remote_Pin ) == 1 ) {
            // 获得此次高电平时间
            Tim = IR_HighLevelPeriod();

            if ( Tim >= 250 )
                break;  // 无用的信号
            if ( Tim >= 200 && Tim < 250 )
                Ok = 1;  // 收到起始信号
            else if ( Tim >= 60 && Tim < 90 )
                Data = 1;  // 收到数据1
            else if ( Tim >= 10 && Tim < 50 )
                Data = 0;  // 收到数据0

            if ( Ok == 1 ) {
                receive_Code <<= 1;
                receive_Code += Data;
                if ( Num >= 32 ) {
                    receive_Flag = 1;
                    break;
                }
            }
            Num++;
        }
    }
}
