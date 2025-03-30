#include "mk60_lptmr.h"
//��ɽ�����
//��˼����MK60�ײ�
//˵��:lptmr�ײ�

//lptmr����ģʽ��ʼ��
void lptmr_counter_init(void)
{
	uint8_t lptmr_alf;
	if(LPTMR_COUNTER_PIN==LPTMR_PA19) 
	{
		lptmr_alf=1;
		gpio_alf_init(PTA,19,ALF6);
	}
	else if(LPTMR_COUNTER_PIN==LPTMR_PC5) 
	{
		lptmr_alf=2;
		gpio_alf_init(PTC,5,ALF4);
	}
	SIM->SCGC5|=1<<0;//�򿪼�����ʱ��
	LPTMR0->CSR=0x00;//�ر�LPTMR
	//ѡ��ʱ��Դ: 0:MCGIRCLK,1:LPO(1KHz),2:ERCLK32K,3:OSCERCLK
	LPTMR0->PSR=LPTMR_PSR_PCS(1)|LPTMR_PSR_PBYP_MASK|LPTMR_PSR_PRESCALE(0);       
  LPTMR0->CMR=65535;//���ñȽ�ֵ
	LPTMR0->CSR=LPTMR_CSR_TPS(lptmr_alf)|LPTMR_CSR_TMS_MASK|0|LPTMR_CSR_TEN_MASK;
}
//�������ֵ������
uint16_t get_lptmr_counter(void)
{
	uint16_t temp;
	temp=LPTMR0->CNR;
	LPTMR0->CSR&=~LPTMR_CSR_TEN_MASK;
	LPTMR0->CSR|=LPTMR_CSR_TEN_MASK;
	return temp;
}

