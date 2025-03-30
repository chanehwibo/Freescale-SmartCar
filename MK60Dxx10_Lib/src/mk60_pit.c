#include "mk60_pit.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:pit底层

//定时器初始化
//PITx:PIT0,PIT1..
//xms:定时xms
void pit_init(uint8_t PITx,uint16_t xms)
{
	SIM->SCGC6|=1<<23;//开启定时器时钟
	PIT->MCR=0X00000000;//打开定时器模块,在调试模式下继续运行
	PIT->CHANNEL[PITx].LDVAL=xms*(BusClock*1000000/1000);//定时时间为xms
	PIT->CHANNEL[PITx].TFLG=0X01;//清除标志位
  PIT->CHANNEL[PITx].TCTRL=0X03;//打开定时器0,开启中断
	switch(PITx)
	{
		case 0:NVIC_EnableIRQ(PIT0_IRQn);break;
		case 1:NVIC_EnableIRQ(PIT1_IRQn);break;
		case 2:NVIC_EnableIRQ(PIT2_IRQn);break;
		case 3:NVIC_EnableIRQ(PIT3_IRQn);break;
		default:break;
	}
}
//清除pit中断标志
//PITx:PIT0,PIT1..
void clear_pit_int_flag(uint8_t PITx)
{
	PIT->CHANNEL[PITx].TFLG=(uint32_t)0X01;//清除标志位	
}
