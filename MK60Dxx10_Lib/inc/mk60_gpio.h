#ifndef _MK60_GPIO_H
#define _MK60_GPIO_H
#include "mk60_sys.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:gpio底层

//引脚复用功能
typedef enum
{
	ALF0=0,    
	ALF1,     
	ALF2,     
	ALF3,     
	ALF4,     
	ALF5,    
	ALF6,     
	ALF7,     
}GPIO_ALF;

//中断模式
typedef enum
{
	DISABLED=0,      
	DMA_RISING,    
	DMA_FALLING,  
	DMA_EITHER,   
	RESERVED,     
	LOGIC_ZERO=8,   
	RISING,       
	FALLING,     
	EITHER,       
	LOGIC_ONE,    
}INT_MODE;

//上拉下拉
typedef enum
{
	PULL_NULL=0,   
  PULL_UP,     
  PULL_DOWN,    
}GPIO_PULL;

//位带操作
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//输入操作
#define PAin(n)    BIT_ADDR(PTA_BASE+0X10,n)  
#define PBin(n)    BIT_ADDR(PTB_BASE+0X10,n)  
#define PCin(n)    BIT_ADDR(PTC_BASE+0X10,n)  
#define PDin(n)    BIT_ADDR(PTD_BASE+0X10,n)  
#define PEin(n)    BIT_ADDR(PTE_BASE+0X10,n)  
//输出操作
#define PAout(n)   BIT_ADDR(PTA_BASE,n) 
#define PBout(n)   BIT_ADDR(PTB_BASE,n) 
#define PCout(n)   BIT_ADDR(PTC_BASE,n) 
#define PDout(n)   BIT_ADDR(PTD_BASE,n) 
#define PEout(n)   BIT_ADDR(PTE_BASE,n) 

//gpio库函数
void gpio_init(GPIO_Type *GPIOx,uint8_t n,uint8_t dir,uint8_t pull);
void gpio_alf_init(GPIO_Type *GPIOx,uint8_t n,uint8_t alf);
void gpio_int_init(GPIO_Type *GPIOx,uint8_t n,uint8_t mode,uint8_t pull);
uint8_t get_gpio_int_flag(PORT_Type *PORTx,uint8_t n);
void clear_gpio_int_flag(PORT_Type *PORTx,uint8_t n);
void gpio_setbit(GPIO_Type *GPIOx,uint8_t n,uint8_t level);
uint8_t gpio_getbit(GPIO_Type *GPIOx,uint8_t n);
void gpio_write(GPIO_Type *GPIOx,uint16_t data);
uint16_t gpio_read(GPIO_Type *GPIOx);
void gpio_turnbit(GPIO_Type *GPIOx,uint8_t n);

#endif
