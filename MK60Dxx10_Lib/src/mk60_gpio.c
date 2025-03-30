#include "mk60_gpio.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:gpio底层,支持位带操作

//gpio初始化
//GPIOx:PTA,PTB...
//n:引脚编号
//dir:引脚方向,1:输出,0:输入
//pull:上拉下拉选择
void gpio_init(GPIO_Type *GPIOx,uint8_t n,uint8_t dir,uint8_t pull)
{
	PORT_Type *PORTx;
	switch((uint32_t)(GPIOx))
	{
		case PTA_BASE:PORTx=PORTA;SIM->SCGC5|=1<<9;break;
		case PTB_BASE:PORTx=PORTB;SIM->SCGC5|=1<<10;break;
		case PTC_BASE:PORTx=PORTC;SIM->SCGC5|=1<<11;break;
		case PTD_BASE:PORTx=PORTD;SIM->SCGC5|=1<<12;break;
		case PTE_BASE:PORTx=PORTE;SIM->SCGC5|=1<<13;break;
		default:break;
	}
	if(pull==PULL_NULL) //不上拉下拉
	{
		PORTx->PCR[n]&=0XFFFFF8FF;
		PORTx->PCR[n]|=0X00000100;
	}
	else//上拉下拉
	{
		PORTx->PCR[n]&=0XFFF0F8ED;
		if(pull==PULL_UP) PORTx->PCR[n]|=0x00000113;//上拉
		else PORTx->PCR[n]|=0x00000112;//下拉
	}
	if(!dir) GPIOx->PDDR&=~(1<<n);
	else GPIOx->PDDR|=1<<n;
}
//gpio复用功能初始化
void gpio_alf_init(GPIO_Type *GPIOx,uint8_t n,uint8_t alf)
{
	PORT_Type *PORTx;
	switch((uint32_t)(GPIOx))
	{
		case PTA_BASE:PORTx=PORTA;SIM->SCGC5|=1<<9;break;
		case PTB_BASE:PORTx=PORTB;SIM->SCGC5|=1<<10;break;
		case PTC_BASE:PORTx=PORTC;SIM->SCGC5|=1<<11;break;
		case PTD_BASE:PORTx=PORTD;SIM->SCGC5|=1<<12;break;
		case PTE_BASE:PORTx=PORTE;SIM->SCGC5|=1<<13;break;
		default:break;
	}
	PORTx->PCR[n]&=0XFFFFF8FF;
	PORTx->PCR[n]|=1<<6;
	PORTx->PCR[n]|=alf<<8;
}
//gpio中断设置
//GPIOx:PTA,PTB...
//n:引脚编号
//mode:中断模式
//pull:上拉下拉选择
void gpio_int_init(GPIO_Type *GPIOx,uint8_t n,uint8_t mode,uint8_t pull)
{
	PORT_Type *PORTx;
	switch((uint32_t)(GPIOx))
	{
		case PTA_BASE:PORTx=PORTA;SIM->SCGC5|=1<<9;NVIC_EnableIRQ(PORTA_IRQn);break;
		case PTB_BASE:PORTx=PORTB;SIM->SCGC5|=1<<10;NVIC_EnableIRQ(PORTB_IRQn);break;
		case PTC_BASE:PORTx=PORTC;SIM->SCGC5|=1<<11;NVIC_EnableIRQ(PORTC_IRQn);break;
		case PTD_BASE:PORTx=PORTD;SIM->SCGC5|=1<<12;NVIC_EnableIRQ(PORTD_IRQn);break;
		case PTE_BASE:PORTx=PORTE;SIM->SCGC5|=1<<13;NVIC_EnableIRQ(PORTE_IRQn);break;
		default:break;
	}
	PORTx->PCR[n]&=0XFFF0F8ED;
	PORTx->PCR[n]|=mode<<16;
	if(pull==PULL_UP) PORTx->PCR[n]|=0x00000113;//上拉
	else PORTx->PCR[n]|=0x00000112;//下拉
	GPIOx->PDDR&=~(1<<n);
}
//获得gpio中断标志
//PORTx:PORTA,PORTB..
//n:引脚编号
//返回:1对应的引脚产生了中断,0没有
uint8_t get_gpio_int_flag(PORT_Type *PORTx,uint8_t n)
{
	return((PORTx->ISFR&(1<<n))==(1<<n)?1:0);	
}
//清除gpio中断标志
//PORTx:PORTA,PORTB..
//n:引脚编号
void clear_gpio_int_flag(PORT_Type *PORTx,uint8_t n)
{
	PORTx->ISFR=1<<n;
}
//设置GPIO某一管脚电平
//GPIOx:PTA,PTB...
//n:引脚编号
//level:电平状态
void gpio_setbit(GPIO_Type *GPIOx,uint8_t n,uint8_t level)
{
	if(!level) GPIOx->PDOR&=~(1<<n);
	else GPIOx->PDOR|=1<<n;
}
//读取GPIO某一管脚电平
//GPIOx:PTA,PTB...
//n:引脚编号
//返回引脚电平
uint8_t gpio_getbit(GPIO_Type *GPIOx,uint8_t n)
{
	uint8_t data;
  if((GPIOx->PDIR&(1<<n))==1<<n) data=1;
	else if((GPIOx->PDIR&(1<<n))==0) data=0;
	return data;
}
//设置GPIO整体电平
//GPIOx:PTA,PTB...
//data:数据
void gpio_write(GPIO_Type *GPIOx,uint16_t data)
{
	GPIOx->PDOR=data;
}
//读取GPIO整体电平
//GPIOx:PTA,PTB...
//返回数据
uint16_t gpio_read(GPIO_Type *GPIOx)
{
	uint16_t data;
  data=GPIOx->PDIR;
	return data;
}
//翻转GPIO某一管脚电平
//GPIOx:PTA,PTB...
//n:引脚编号
void gpio_turnbit(GPIO_Type *GPIOx,uint8_t n)
{
	GPIOx->PTOR|=1<<n;
}

