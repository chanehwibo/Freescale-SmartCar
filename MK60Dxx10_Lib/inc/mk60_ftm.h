#ifndef _MK60_FTM_H
#define _MK60_FTM_H
#include "mk60_sys.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:ftm底层

//FTM通道
typedef enum
{
	ftm_ch0=0,
	ftm_ch1,
	ftm_ch2,
	ftm_ch3,
	ftm_ch4,
	ftm_ch5,
	ftm_ch6,
	ftm_ch7,
}FTM_Channel;

//FTM计数器时钟分频
typedef enum
{
	ftm_clk_divide1=0,
	ftm_clk_divide2,
	ftm_clk_divide4,
	ftm_clk_divide8,
	ftm_clk_divide16,
	ftm_clk_divide32,
	ftm_clk_divide64,
	ftm_clk_divide128,
}FTM_Clk_Divide;

//FTM管脚
typedef enum
{
////FTM0管脚//////
  FTM_PA3=0,//FTM0_CH0//ALF3
  FTM_PA4,//FTM0_CH1
  FTM_PA5,//FTM0_CH2
	FTM_PA6,//FTM0_CH3
	FTM_PA7,//FTM0_CH4
	FTM_PA0,//FTM0_CH5
	FTM_PA1,//FTM0_CH6
	FTM_PA2,//FTM0_CH7
	FTM_PC1,//FTM0_CH0//ALF4
	FTM_PC2,//FTM0_CH1
	FTM_PC3,//FTM0_CH2
	FTM_PC4,//FTM0_CH3
	FTM_PD4,//FTM0_CH4
	FTM_PD5,//FTM0_CH5
	FTM_PD6,//FTM0_CH6
	FTM_PD7,//FTM0_CH7
////FTM1管脚//////
	FTM_PA8,//FTM1_CH0//ALF3
	FTM_PA9,//FTM1_CH1
	FTM_PA12,//FTM1_CH0//ALF3
	FTM_PA13,//FTM1_CH1
	FTM_PB0,//FTM1_CH0//ALF3
	FTM_PB1,//FTM1_CH1
////FTM2管脚//////
	FTM_PA10,//FTM2_CH0//ALF3
	FTM_PA11,//FTM2_CH1
	FTM_PB18,//FTM2_CH0//ALF3
	FTM_PB19,//FTM2_CH1
}FTM_Pin;

extern uint8_t FTM1_QUAD_DIR,FTM2_QUAD_DIR; 

//FTM库函数
void ftm_pwm_init(FTM_Type *FTMx,uint8_t channel,uint16_t mod,uint16_t cnv);
void ftm_duty_change(FTM_Type *FTMx,uint8_t channel,uint32_t duty);
void ftm_quad_init(FTM_Type *FTMx,uint8_t channel);
uint16_t get_ftm_quad_counter(FTM_Type *FTMx);

#endif
