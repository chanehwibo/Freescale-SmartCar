#ifndef _K60_DMA_H
#define _K60_DMA_H
#include "mk60_sys.h"
#include "mk60_gpio.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:dma底层

#define vu8  volatile unsigned char 
#define vu16 volatile unsigned short 
#define vu32 volatile unsigned int

#define DMA_DreqEnable(Channel)  (DMA0->ERQ|=1<<Channel)   //开启DMA通道请求
#define DMA_DreqDisable(Channel) (DMA0->ERQ&=~(1<<Channel))//关闭DMA通道请求
#define DMA_ResetSourceAddress(DMA_Channel,Source_Address) (DMA0->TCD[DMA_Channel].SADDR=Source_Address)//重新设置源地址
#define DMA_ResetDestAddress(DMA_Channel,Dest_Address)     (DMA0->TCD[DMA_Channel].DADDR=Dest_Address)  //重新设置目标地址
#define DMA_ClearIntFlag(DMA_Channel) (DMA0->INT|=1<<DMA_Channel) //清除DMA中断标志位

//DMA外设请求号
typedef enum
{
	//USART
	UART0_RX_DMAREQ=2,
	UART0_TX_DMAREQ=3,
	UART1_RX_DMAREQ=4,
	UART1_TX_DMAREQ=5,
	UART2_RX_DMAREQ=6,
	UART2_TX_DMAREQ=7,
	UART3_RX_DMAREQ=8,
	UART3_TX_DMAREQ=9,
	UART4_RX_DMAREQ=10,
	UART4_TX_DMAREQ=11,
	UART5_RX_DMAREQ=12,
	UART5_TX_DMAREQ=13,
	//I2S
	I2S0_RX_DMAREQ=14,
	I2S0_TX_DMAREQ=15,
	//SPI
	SPI0_RX_DMAREQ=16,
	SPI0_TX_DMAREQ=17,
	SPI1_RX_DMAREQ=18,
	SPI1_TX_DMAREQ=19,
	//I2C
	I2C0_DMAREQ=22,
	I2C1_DMAREQ=23,
	//FTM0
	FTM0_CH0_DMAREQ=24,
  FTM0_CH1_DMAREQ=25,
  FTM0_CH2_DMAREQ=26,
  FTM0_CH3_DMAREQ=27,
  FTM0_CH4_DMAREQ=28,
  FTM0_CH5_DMAREQ=29,
  FTM0_CH6_DMAREQ=30,
  FTM0_CH7_DMAREQ=31,
	//FTM1
	FTM1_CH0_DMAREQ=32,
  FTM1_CH1_DMAREQ=33,
	//FTM2
	FTM2_CH0_DMAREQ=34,
  FTM2_CH1_DMAREQ=35,
	//FTM3
	FTM3_CH0_DMAREQ=36,
  FTM3_CH1_DMAREQ=37,
	FTM3_CH2_DMAREQ=38,
  FTM3_CH3_DMAREQ=39,
	//SDC
	ADC0_DMAREQ=40,
  ADC1_DMAREQ=41,
	//CMP
	CMP0_DMAREQ=42,
	CMP1_DMAREQ=43,
	CMP2_DMAREQ=44,
	//DAC
	DAC0_DMAREQ=45,
	DAC1_DMAREQ=46,
	//CMT
	CMT_DMAREQ=47,
	//PDB
	PDB_DMAREQ=48,
	//PORT
	PORTA_DMAREQ=49,
  PORTB_DMAREQ=50,
  PORTC_DMAREQ=51,
  PORTD_DMAREQ=52,
  PORTE_DMAREQ=53,
	//FTM
	FTM3_CH4_DMAREQ=54,
	FTM3_CH5_DMAREQ=55,
	FTM3_CH6_DMAREQ=56,
	FTM3_CH7_DMAREQ=57,
	//ALWAYS_ENABLE
	ALWAYS_ENABLE1_DMAREQ=58,
	ALWAYS_ENABLE2_DMAREQ=59,
	ALWAYS_ENABLE3_DMAREQ=60,
	ALWAYS_ENABLE4_DMAREQ=61,
	ALWAYS_ENABLE5_DMAREQ=62,
	ALWAYS_ENABLE6_DMAREQ=63,
}DMA_Periph;

//DMA通道
typedef enum
{
	DMA_Channel0=0,
	DMA_Channel1,
	DMA_Channel2,
	DMA_Channel3,
	DMA_Channel4,
	DMA_Channel5,
	DMA_Channel6,
	DMA_Channel7,
	DMA_Channel8,
	DMA_Channel9,
	DMA_Channel10,
	DMA_Channel11,
	DMA_Channel12,
	DMA_Channel13,
	DMA_Channel14,
	DMA_Channel15,	
}DMA_Channel;

void dma_gpio_to_buffer(unsigned char DMA_Channel,unsigned char Periph,unsigned int Source_Address,unsigned int Dest_Address,unsigned short DmaTransNums);
void dma_gpio_counter_init(unsigned char DMA_Channel,GPIO_Type *GPIOx,unsigned char n,unsigned char mode,unsigned char pull);
unsigned short dma_get_counter(unsigned char DMA_Channel);

#endif
