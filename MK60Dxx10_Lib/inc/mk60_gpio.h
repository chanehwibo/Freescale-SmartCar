#ifndef _MK60_GPIO_H
#define _MK60_GPIO_H
#include "mk60_sys.h"
//��ɽ�����
//��˼����MK60�ײ�
//˵��:gpio�ײ�

//���Ÿ��ù���
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

//�ж�ģʽ
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

//��������
typedef enum
{
	PULL_NULL=0,   
  PULL_UP,     
  PULL_DOWN,    
}GPIO_PULL;

//λ������
#define BITBAND(addr, bitnum) ((addr & 0xF0000000)+0x2000000+((addr &0xFFFFF)<<5)+(bitnum<<2)) 
#define MEM_ADDR(addr)  *((volatile unsigned long  *)(addr)) 
#define BIT_ADDR(addr, bitnum)   MEM_ADDR(BITBAND(addr, bitnum)) 
//�������
#define PAin(n)    BIT_ADDR(PTA_BASE+0X10,n)  
#define PBin(n)    BIT_ADDR(PTB_BASE+0X10,n)  
#define PCin(n)    BIT_ADDR(PTC_BASE+0X10,n)  
#define PDin(n)    BIT_ADDR(PTD_BASE+0X10,n)  
#define PEin(n)    BIT_ADDR(PTE_BASE+0X10,n)  
//�������
#define PAout(n)   BIT_ADDR(PTA_BASE,n) 
#define PBout(n)   BIT_ADDR(PTB_BASE,n) 
#define PCout(n)   BIT_ADDR(PTC_BASE,n) 
#define PDout(n)   BIT_ADDR(PTD_BASE,n) 
#define PEout(n)   BIT_ADDR(PTE_BASE,n) 

//gpio�⺯��
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
