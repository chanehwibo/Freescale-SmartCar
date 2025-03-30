#ifndef _MK60_PIT_H
#define _MK60_PIT_H
#include "mk60_sys.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:pit底层

//定时器编号
typedef enum
{
	PIT0=0,   
  PIT1,   
  PIT2,   
  PIT3,   
}PITx;

//定时器库函数
void pit_init(uint8_t PITx,uint16_t xms);
void clear_pit_int_flag(uint8_t PITx);

#endif
