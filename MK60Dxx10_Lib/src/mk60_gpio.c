#include "mk60_gpio.h"
//��ɽ�����
//��˼����MK60�ײ�
//˵��:gpio�ײ�,֧��λ������

//gpio��ʼ��
//GPIOx:PTA,PTB...
//n:���ű��
//dir:���ŷ���,1:���,0:����
//pull:��������ѡ��
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
	if(pull==PULL_NULL) //����������
	{
		PORTx->PCR[n]&=0XFFFFF8FF;
		PORTx->PCR[n]|=0X00000100;
	}
	else//��������
	{
		PORTx->PCR[n]&=0XFFF0F8ED;
		if(pull==PULL_UP) PORTx->PCR[n]|=0x00000113;//����
		else PORTx->PCR[n]|=0x00000112;//����
	}
	if(!dir) GPIOx->PDDR&=~(1<<n);
	else GPIOx->PDDR|=1<<n;
}
//gpio���ù��ܳ�ʼ��
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
//gpio�ж�����
//GPIOx:PTA,PTB...
//n:���ű��
//mode:�ж�ģʽ
//pull:��������ѡ��
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
	if(pull==PULL_UP) PORTx->PCR[n]|=0x00000113;//����
	else PORTx->PCR[n]|=0x00000112;//����
	GPIOx->PDDR&=~(1<<n);
}
//���gpio�жϱ�־
//PORTx:PORTA,PORTB..
//n:���ű��
//����:1��Ӧ�����Ų������ж�,0û��
uint8_t get_gpio_int_flag(PORT_Type *PORTx,uint8_t n)
{
	return((PORTx->ISFR&(1<<n))==(1<<n)?1:0);	
}
//���gpio�жϱ�־
//PORTx:PORTA,PORTB..
//n:���ű��
void clear_gpio_int_flag(PORT_Type *PORTx,uint8_t n)
{
	PORTx->ISFR=1<<n;
}
//����GPIOĳһ�ܽŵ�ƽ
//GPIOx:PTA,PTB...
//n:���ű��
//level:��ƽ״̬
void gpio_setbit(GPIO_Type *GPIOx,uint8_t n,uint8_t level)
{
	if(!level) GPIOx->PDOR&=~(1<<n);
	else GPIOx->PDOR|=1<<n;
}
//��ȡGPIOĳһ�ܽŵ�ƽ
//GPIOx:PTA,PTB...
//n:���ű��
//�������ŵ�ƽ
uint8_t gpio_getbit(GPIO_Type *GPIOx,uint8_t n)
{
	uint8_t data;
  if((GPIOx->PDIR&(1<<n))==1<<n) data=1;
	else if((GPIOx->PDIR&(1<<n))==0) data=0;
	return data;
}
//����GPIO�����ƽ
//GPIOx:PTA,PTB...
//data:����
void gpio_write(GPIO_Type *GPIOx,uint16_t data)
{
	GPIOx->PDOR=data;
}
//��ȡGPIO�����ƽ
//GPIOx:PTA,PTB...
//��������
uint16_t gpio_read(GPIO_Type *GPIOx)
{
	uint16_t data;
  data=GPIOx->PDIR;
	return data;
}
//��תGPIOĳһ�ܽŵ�ƽ
//GPIOx:PTA,PTB...
//n:���ű��
void gpio_turnbit(GPIO_Type *GPIOx,uint8_t n)
{
	GPIOx->PTOR|=1<<n;
}

