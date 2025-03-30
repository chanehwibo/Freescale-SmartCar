#include "mk60_sys.h"
//��ɽ�����
//��˼����MK60�ײ�
//˵��:ϵͳʱ�ӳ�ʼ���ײ�

//����K60ʱ��
//�ں�/ϵͳʱ��Ϊ:150/1=150MHz
//Busʱ��Ϊ:150/1=150MHz
//FlexBusʱ��Ϊ150/15=10MHz
//Flashʱ��Ϊ:150/10=15MHz
void SystemInit(void)
{
	 WDOG->UNLOCK=0xC520;//�رտ��Ź�
	 WDOG->UNLOCK=0xD928;  
	 WDOG->STCTRLH&=~0x0001;
	 //ģʽ�л�:FEI->FBE->PBE->PEE
	 MCG->C1&=0X03;
	 MCG->C1|=0XB8;
	 MCG->C2&=0XCD;
	 MCG->C2|=0X10;
	 while(MCG->S&0X10);
	 while((MCG->S&0X0C)>>2!=0X02);
	 SIM->CLKDIV1=(SIM_CLKDIV1_OUTDIV1(PllClock/SystemClock-1)|SIM_CLKDIV1_OUTDIV2(PllClock/BusClock-1)|SIM_CLKDIV1_OUTDIV3(PllClock/FlexClock-1)|SIM_CLKDIV1_OUTDIV4(PllClock/FlashClock-1));
	 MCG->C5&=0XE0; //�����Ƶλ
	 MCG->C5|=((ExternalClock/5)-1)<<0; //ExternalClock/(ExternalClock/5)=5MHz
	 MCG->C6&=0XD0; //�����Ƶλ
	 MCG->C6|=1<<6;
	 MCG->C6|=(PllClock/5-24)<<0; //��Ƶϵ��
	 while((MCG->S&0X20)!=0X20);
	 while((MCG->S&0X40)!=0X40);
	 MCG->C1&=0X31;
	 MCG->C1|=0X00;
	 while((MCG->S&0X0C)>>2!=0X03);
}
//����ȫ���ж�
void EnableInterrupts(void)
{
	__enable_irq();
}
//�ر�ȫ���ж�
void DisableInterrupts(void)
{
	__disable_irq();
}
//�����ж����ȼ�
//PrioGroup:Group0~Group7
//IRQn:�ж�����
//prio:�������ȼ�,ԽС���ȼ�Խ��
void SetIntPrio(uint32_t PrioGroup,IRQn_Type IRQn,uint32_t prio)
{
	NVIC_SetPriorityGrouping(PrioGroup);
  NVIC_SetPriority(IRQn,prio);	
}
//΢�뼶
void delay_us(uint16_t nus)
{
	uint32_t temp;
	SysTick->CTRL|=0x04;//����ϵͳ�δ�ʱ����ʱ��Ϊ�ں�ʱ��
  SysTick->LOAD=nus*SystemClock;//ʱ�����
  SysTick->VAL=0x00;//��ռ�����
  SysTick->CTRL|=0x01;//��ʼ����   
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//�ȴ�ʱ�䵽��   
	SysTick->CTRL&=~0x01;//�رռ�����
}
//���뼶
void delay_ms(uint16_t nms)
{
	uint16_t t;
	for(t=0;t<nms;t++)
	{
		delay_us(1000);
	}
}

