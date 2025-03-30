#include "mk60_ftm.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:ftm底层

uint8_t FTM1_QUAD_DIR; //FTM1正交解码方向标志
uint8_t FTM2_QUAD_DIR; //FTM2正交解码方向标志

//FTM PWM模式初始化
//FTMx:FTM0,FTM1,FTM2
//channel:FTM通道选择
//mod:PWM计数总数
//cnv:占空比
void ftm_pwm_init(FTM_Type *FTMx,uint8_t channel,uint16_t mod,uint16_t cnv)
{
	FTM_Type *ftmx;
	uint8_t ftm_clk_divide; 
	switch((uint32_t)FTMx)
	{
		case FTM0_BASE:
		{
			SIM->SCGC6|=1<<24;
			ftmx=FTM0;
			ftm_clk_divide=FTM0_CLK_DIVIDE;
			if(FTM0_CH0==FTM_PA3) gpio_alf_init(PTA,3,ALF3);
			else if(FTM0_CH0==FTM_PC1) gpio_alf_init(PTC,1,ALF4);
			if(FTM0_CH1==FTM_PA4) gpio_alf_init(PTA,4,ALF3);
			else if(FTM0_CH1==FTM_PC2) gpio_alf_init(PTC,2,ALF4);
			if(FTM0_CH2==FTM_PA5) gpio_alf_init(PTA,5,ALF3);
			else if(FTM0_CH2==FTM_PC3) gpio_alf_init(PTC,3,ALF4);
			if(FTM0_CH3==FTM_PA6) gpio_alf_init(PTA,6,ALF3);
			else if(FTM0_CH3==FTM_PC4) gpio_alf_init(PTC,4,ALF4);
			if(FTM0_CH4==FTM_PA7) gpio_alf_init(PTA,7,ALF3);
			else if(FTM0_CH4==FTM_PD4) gpio_alf_init(PTD,4,ALF4);
			if(FTM0_CH5==FTM_PA0) gpio_alf_init(PTA,0,ALF3);
			else if(FTM0_CH5==FTM_PD5) gpio_alf_init(PTD,5,ALF4);
			if(FTM0_CH6==FTM_PA1) gpio_alf_init(PTA,1,ALF3);
			else if(FTM0_CH6==FTM_PD6) gpio_alf_init(PTD,6,ALF4);
			if(FTM0_CH7==FTM_PA2) gpio_alf_init(PTA,2,ALF3);
			else if(FTM0_CH7==FTM_PD7) gpio_alf_init(PTD,7,ALF4);
		  break;
		}
		case FTM1_BASE:
		{
			SIM->SCGC6|=1<<25;
			ftmx=FTM1;
			ftm_clk_divide=FTM1_CLK_DIVIDE;
			if(FTM1_CH0==FTM_PA8) gpio_alf_init(PTA,8,ALF3);
			else if(FTM1_CH0==FTM_PA12) gpio_alf_init(PTA,12,ALF3);
			else if(FTM1_CH0==FTM_PB0) gpio_alf_init(PTB,0,ALF3);
			if(FTM1_CH1==FTM_PA9) gpio_alf_init(PTA,9,ALF3);
			else if(FTM1_CH1==FTM_PA13) gpio_alf_init(PTA,13,ALF3);
			else if(FTM1_CH1==FTM_PB1) gpio_alf_init(PTB,1,ALF3);
		  break;
		}
		case FTM2_BASE:
		{
			SIM->SCGC3|=1<<24;
			ftmx=FTM2;
			ftm_clk_divide=FTM2_CLK_DIVIDE;
			if(FTM2_CH0==FTM_PA10) gpio_alf_init(PTA,10,ALF3);
			else if(FTM2_CH0==FTM_PB18) gpio_alf_init(PTB,18,ALF3);
			if(FTM2_CH1==FTM_PA11) gpio_alf_init(PTA,11,ALF3);
			else if(FTM2_CH1==FTM_PB19) gpio_alf_init(PTB,19,ALF3);
			break;
		}
		default:break;
	}
	ftmx->MODE|=1<<2;//去写保护
	ftmx->CONTROLS[channel].CnSC&=~(0X3<<2);//清除ELSB:ELSA位
	ftmx->CONTROLS[channel].CnSC|=0X2<<2; //ELSB:ELSA=1:0
	ftmx->CONTROLS[channel].CnSC&=~(0X3<<4); //清除MSB:MSA位
	ftmx->CONTROLS[channel].CnSC|=0X2<<4;//MSB:MSA=1:0
	ftmx->SC|=1<<5; //CPWMS=1
	ftmx->SC|=0X1<<3; //FTM使用SystemClock
	ftmx->SC&=~(0X7<<0);//清除分频位
	switch((uint32_t)ftm_clk_divide)//设置分频系数
	{
		case ftm_clk_divide1:ftmx->SC&=~(0X7<<0);break;
		case ftm_clk_divide2:ftmx->SC|=0X1<<0;break;
		case ftm_clk_divide4:ftmx->SC|=0X2<<0;break;
		case ftm_clk_divide8:ftmx->SC|=0X3<<0;break;
		case ftm_clk_divide16:ftmx->SC|=0X4<<0;break;
		case ftm_clk_divide32:ftmx->SC|=0X5<<0;break;
		case ftm_clk_divide64:ftmx->SC|=0X6<<0;break;
		case ftm_clk_divide128:ftmx->SC|=0X7<<0;break;
		default:break;
	}
	ftmx->CNTIN=0;//计数器初值
	ftmx->MOD=mod;//计数器终值
	ftmx->CONTROLS[channel].CnV=cnv;//占空比
	ftmx->CNT=0;//计数器清零
	ftmx->MODE|=1<<1;//使能FTM 
}
//改变FTM通道占空比
//FTMx:FTM0,FTM1,FTM2
//channel:FTM通道选择
//duty:占空比
void ftm_duty_change(FTM_Type *FTMx,uint8_t channel,uint32_t duty)
{
	FTMx->CONTROLS[channel].CnV=duty;//高电平时间
}
//FTM PWM正交解码初始化
//FTMx:FTM1,FTM2
//channel:FTM通道选择
void ftm_quad_init(FTM_Type *FTMx,uint8_t channel)
{
	FTM_Type *ftmx;
	switch((uint32_t)FTMx)
	{
		case FTM1_BASE:
		{
			SIM->SCGC6|=1<<25;
			ftmx=FTM1;
			if(FTM1_CH0==FTM_PA8) gpio_alf_init(PTA,8,ALF6);
			else if(FTM1_CH0==FTM_PA12) gpio_alf_init(PTA,12,ALF7);
			else if(FTM1_CH0==FTM_PB0) gpio_alf_init(PTB,0,ALF6);
			if(FTM1_CH1==FTM_PA9) gpio_alf_init(PTA,9,ALF6);
			else if(FTM1_CH1==FTM_PA13) gpio_alf_init(PTA,13,ALF7);
			else if(FTM1_CH1==FTM_PB1) gpio_alf_init(PTB,1,ALF6);
		  break;
		}
		case FTM2_BASE:
		{
			SIM->SCGC3|=1<<24;
			ftmx=FTM2;
			if(FTM2_CH0==FTM_PA10) gpio_alf_init(PTA,10,ALF6);
			else if(FTM2_CH0==FTM_PB18) gpio_alf_init(PTB,18,ALF6);
			if(FTM2_CH1==FTM_PA11) gpio_alf_init(PTA,11,ALF6);
			else if(FTM2_CH1==FTM_PB19) gpio_alf_init(PTB,19,ALF6);
			break;
		}
		default:break;
	}
	ftmx->MODE|=1<<2;//去写保护
	ftmx->QDCTRL&=~(1<<3); //AB相同确定方向和计数值
	ftmx->CNTIN=0;//计数器初值
	ftmx->MOD=65535;//计数器终值
	ftmx->QDCTRL|=1<<0; //启用FTM正交解码
	ftmx->MODE|=1<<0; //FTMEN=1  
	ftmx->SC|=0X1<<3; //使用SystemClock
	ftmx->CNT=0;//计数器清零
}
//获取正交解码的脉冲数并清零
//FTMx:FTM1,FTM2
uint16_t get_ftm_quad_counter(FTM_Type *FTMx)
{
	uint16_t temp=FTMx->CNT;
	if((FTMx->QDCTRL&(1<<2))==0) //递减
	{
		temp=65536-temp; //取反向
		if((uint32_t)FTMx==FTM1_BASE) FTM1_QUAD_DIR=0;
		else if((uint32_t)FTMx==FTM2_BASE) FTM2_QUAD_DIR=0;
	}
	else if((FTMx->QDCTRL&(1<<2))==1<<2) //递加
	{
		if((uint32_t)FTMx==FTM1_BASE) FTM1_QUAD_DIR=1;
		else if((uint32_t)FTMx==FTM2_BASE) FTM2_QUAD_DIR=1;
	}
	FTMx->CNT=0;
	return temp;
}
