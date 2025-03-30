#ifndef _MK60_LPTMR_H
#define _MK60_LPTMR_H
#include "mk60_sys.h"
//��ɽ�����
//��˼����MK60�ײ�
//˵��:lptmr�ײ�

//LPTMR��������
typedef enum
{
	LPTMR_PC5=0,
	LPTMR_PA19,
}LPTMR_Pin;

//LPTMR�⺯��
void lptmr_counter_init(void);
uint16_t get_lptmr_counter(void);

#endif
