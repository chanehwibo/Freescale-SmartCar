#ifndef _MK60_PIT_H
#define _MK60_PIT_H
#include "mk60_sys.h"
//��ɽ�����
//��˼����MK60�ײ�
//˵��:pit�ײ�

//��ʱ�����
typedef enum
{
	PIT0=0,   
  PIT1,   
  PIT2,   
  PIT3,   
}PITx;

//��ʱ���⺯��
void pit_init(uint8_t PITx,uint16_t xms);
void clear_pit_int_flag(uint8_t PITx);

#endif
