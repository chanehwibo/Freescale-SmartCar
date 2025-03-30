#ifndef _MK60_ADC_H
#define _MK60_ADC_H
#include "mk60_sys.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:adc底层

//ADC管脚
typedef enum
{
	//ADC0
	ADC0_PB0=8,       //PTB0
	ADC0_PB1=9,       //PTB1
	ADC0_PA7=10,      //PTA7
	ADC0_PA8=11,      //PTA8
	ADC0_PB2=12,      //PTB2
	ADC0_PB3=13,      //PTB3
	ADC0_PC0=14,      //PTC0
	ADC0_PC1=15,      //PTC1
	ADC0_PE24=17,     //PTE24
	ADC0_PE25=18,     //PTE25
	//ADC1
	ADC1_PE0=36,      //PTE0
	ADC1_PE1=37,      //PTE1
	ADC1_PE2=38,      //PTE2
	ADC1_PE3=39,      //PTE3
	ADC1_PB0=44,      //PTB0
	ADC1_PB1=45,      //PTB1
	ADC1_PB4=46,      //PTB4
	ADC1_PB5=47,      //PTB5
	ADC1_PB6=48,      //PTB6
	ADC1_PB7=49,      //PTB7
	ADC1_PB10=50,     //PTB10
	ADC1_PB11=51,     //PTB11
	ADC1_PA17=53,     //PTA17
}ADC_Pin;

//ADC采样位数
typedef enum
{
	ADC_8bit=0,
	ADC_12bit,
	ADC_10bit,
	ADC_16bit,
}ADC_Bit;

//ADC库函数
void adc_init(ADC_Type *ADCx,uint8_t channel,uint8_t adc_bit);
uint16_t get_adc_data(ADC_Type *ADCx,uint8_t channel);

#endif
