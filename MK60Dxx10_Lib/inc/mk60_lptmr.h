#ifndef _MK60_LPTMR_H
#define _MK60_LPTMR_H
#include "mk60_sys.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:lptmr底层

//LPTMR计数引脚
typedef enum
{
	LPTMR_PC5=0,
	LPTMR_PA19,
}LPTMR_Pin;

//LPTMR库函数
void lptmr_counter_init(void);
uint16_t get_lptmr_counter(void);

#endif
