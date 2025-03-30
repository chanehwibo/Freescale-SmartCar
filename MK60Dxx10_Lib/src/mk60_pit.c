#include "mk60_pit.h"
//��ɽ�����
//��˼����MK60�ײ�
//˵��:pit�ײ�

//��ʱ����ʼ��
//PITx:PIT0,PIT1..
//xms:��ʱxms
void pit_init(uint8_t PITx,uint16_t xms)
{
	SIM->SCGC6|=1<<23;//������ʱ��ʱ��
	PIT->MCR=0X00000000;//�򿪶�ʱ��ģ��,�ڵ���ģʽ�¼�������
	PIT->CHANNEL[PITx].LDVAL=xms*(BusClock*1000000/1000);//��ʱʱ��Ϊxms
	PIT->CHANNEL[PITx].TFLG=0X01;//�����־λ
  PIT->CHANNEL[PITx].TCTRL=0X03;//�򿪶�ʱ��0,�����ж�
	switch(PITx)
	{
		case 0:NVIC_EnableIRQ(PIT0_IRQn);break;
		case 1:NVIC_EnableIRQ(PIT1_IRQn);break;
		case 2:NVIC_EnableIRQ(PIT2_IRQn);break;
		case 3:NVIC_EnableIRQ(PIT3_IRQn);break;
		default:break;
	}
}
//���pit�жϱ�־
//PITx:PIT0,PIT1..
void clear_pit_int_flag(uint8_t PITx)
{
	PIT->CHANNEL[PITx].TFLG=(uint32_t)0X01;//�����־λ	
}
