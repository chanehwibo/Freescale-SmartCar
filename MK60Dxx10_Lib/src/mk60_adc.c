#include "mk60_adc.h"
//��ɽ��
//��˼����MK60�ײ�
//˵��:adc�ײ�

//ADC��ʼ��
//ADCx:ADC0,ADC1
//channel:ADCͨ��ѡ��
void adc_init(ADC_Type *ADCx,uint8_t channel,uint8_t adc_bit)
{
	switch((uint32_t)(ADCx))
	{
		case ADC0_BASE:
			SIM->SCGC6|=SIM_SCGC6_ADC0_MASK;
		  SIM->SOPT7&=~(SIM_SOPT7_ADC0ALTTRGEN_MASK|SIM_SOPT7_ADC0PRETRGSEL_MASK);
      SIM->SOPT7=SIM_SOPT7_ADC0TRGSEL(0);
		  break;
		case ADC1_BASE:
			SIM->SCGC3|=SIM_SCGC3_ADC1_MASK;
      SIM->SOPT7&=~(SIM_SOPT7_ADC1ALTTRGEN_MASK|SIM_SOPT7_ADC1PRETRGSEL_MASK);
      SIM->SOPT7=SIM_SOPT7_ADC1TRGSEL(0);
		  break;
		default:break;
	}
	switch(channel)
	{
		//ADC0
		case ADC0_PB0:  gpio_alf_init(PTB,0,ALF0); break;
		case ADC0_PB1:  gpio_alf_init(PTB,1,ALF0); break;
		case ADC0_PA7:  gpio_alf_init(PTA,7,ALF0); break;
		case ADC0_PA8:  gpio_alf_init(PTA,8,ALF0); break;
		case ADC0_PB2:  gpio_alf_init(PTB,2,ALF0); break;
		case ADC0_PB3:  gpio_alf_init(PTB,3,ALF0); break;
		case ADC0_PC0:  gpio_alf_init(PTC,0,ALF0); break;
		case ADC0_PC1:  gpio_alf_init(PTC,1,ALF0); break;
		case ADC0_PE24: gpio_alf_init(PTE,24,ALF0); break;
		case ADC0_PE25: gpio_alf_init(PTE,25,ALF0); break;	
		//ADC1
		case ADC1_PE0:  gpio_alf_init(PTE,0,ALF0); break;
		case ADC1_PE1:  gpio_alf_init(PTE,1,ALF0); break;
		case ADC1_PE2:  gpio_alf_init(PTE,2,ALF0); break;
		case ADC1_PE3:  gpio_alf_init(PTE,3,ALF0); break;
		case ADC1_PB0:  gpio_alf_init(PTB,0,ALF0); break;
		case ADC1_PB1:  gpio_alf_init(PTB,1,ALF0); break;
		case ADC1_PB4:  gpio_alf_init(PTB,4,ALF0); break;
		case ADC1_PB5:  gpio_alf_init(PTB,5,ALF0); break;
		case ADC1_PB6:  gpio_alf_init(PTB,6,ALF0); break;
		case ADC1_PB7:  gpio_alf_init(PTB,7,ALF0); break;
		case ADC1_PB10: gpio_alf_init(PTB,10,ALF0); break;
		case ADC1_PB11: gpio_alf_init(PTB,11,ALF0); break;
		case ADC1_PA17: gpio_alf_init(PTA,17,ALF0); break;
		default:break;
	}
	ADCx->CFG1&=~(0X3<<2);//���ADת��λ��
	ADCx->CFG1|=adc_bit<<2; //����ADת��λ��
	ADCx->CFG1&=~(0X3<<0);//����ʱ��ԴλBusClock
	ADCx->CFG1|=1<<4;//������ʱ��
	ADCx->CFG1&=~(0X3<<5);
	ADCx->CFG1|=0X2<<5; //����ADCʱ��4��Ƶ
	ADCx->SC1[0]&=~(1<<5);//�ǲ������
}
//����һ��ת��
uint16_t get_adc_data(ADC_Type *ADCx,uint8_t channel)
{
	ADCx->SC1[0]&=~(0X1F<<0);		    
	ADCx->SC1[0]|=channel<<0; 
	while((ADCx->SC1[0]&1<<7)==1<<7); //�ȴ�ת�����
	return ADCx->R[0]; //����ADֵ
}

