#ifndef _MK60_SYS_H
#define _MK60_SYS_H
#include "string.h"
#include "MK60DZ10.h"
#include "mk60_gpio.h"
#include "mk60_uart.h"
#include "mk60_pit.h"
//#include "mk60_dma.h"
#include "mk60_spi.h"
#include "mk60_lptmr.h"
#include "mk60_ftm.h"
#include "mk60_adc.h"
#include "k60_dma.h"
//��ɽ�����
//��˼����MK60�ײ�
//˵��:ϵͳʱ�ӳ�ʼ���ײ�
//��������
#ifndef u8
#define u8  uint8_t 
#endif
#ifndef u16
#define u16 uint16_t 
#endif
#ifndef u32
#define u32 uint32_t 
#endif

//ϵͳʱ�Ӷ���
#define ExternalClock  50  //����Ƶ��,����Ϊ5�ı���,����̫��
#define PllClock       150 //���໷���ʱ�� (120Mhz~275Mhz)����Ϊ5�ı���
#define SystemClock    150 //ϵͳʱ��(�ܱ�PllClock����,���Ľ��������16)
#define BusClock       150 //����ʱ��(�ܱ�PllClock����,���Ľ��������16)
#define FlexClock      15  //FlexClockʱ��(�ܱ�PllClock����,���Ľ��������16)
#define FlashClock     10  //FlashClockʱ��(�ܱ�PllClock����,���Ľ��������16)

/////////////////////��������ѡ��//////////////////////

//UARTģ��
#define USE_RX   0//���չر�
#define UART_TX  UART_PE24//TXD��RXDѡ��
#define UART_RX  UART_PE25
#define UART_Printf UART4

//SPIģ��
#define SPI0_SCK   SPI_PA15 //SPI0����
#define SPI0_MOSI  SPI_PA16 
#define SPI0_MISO  SPI_PA17 
#define SPI1_SCK   SPI_PE2 //SPI1����
#define SPI1_MOSI  SPI_PE1
#define SPI1_MISO  SPI_PE3 
#define SPI2_SCK   SPI_PB21 //SPI2����
#define SPI2_MOSI  SPI_PB22
#define SPI2_MISO  SPI_PB23 

//FTMģ��
#define FTM0_CLK_DIVIDE  ftm_clk_divide4 //FTM0ʱ�ӷ�Ƶ  
#define FTM1_CLK_DIVIDE  ftm_clk_divide64 //FTM1ʱ�ӷ�Ƶ  
#define FTM2_CLK_DIVIDE  ftm_clk_divide64 //FTM2ʱ�ӷ�Ƶ 
#define FTM0_CH0   FTM_PC1//FTM0 7��ͨ����������
#define FTM0_CH1   FTM_PC2
#define FTM0_CH2   FTM_PC3
#define FTM0_CH3   FTM_PC4
#define FTM0_CH4   FTM_PA7
#define FTM0_CH5   FTM_PA0
#define FTM0_CH6   FTM_PA1
#define FTM0_CH7   FTM_PA2
#define FTM1_CH0   FTM_PA12//FTM1 2��ͨ����������
#define FTM1_CH1   FTM_PA13
#define FTM2_CH0   FTM_PA10//FTM2 2��ͨ����������
#define FTM2_CH1   FTM_PA11

//ADCģ��
//��mk60_adc.h�в鿴

//LPTMRģ��
#define LPTMR_COUNTER_PIN  LPTMR_PC5//��ѡ(PC5,PA19)

//DMAģ��
#define DMA_INT 0//�ر�DMA�ж�
////////////////////////////////////////////////////////

//ϵͳ����
void SystemInit(void);
void EnableInterrupts(void);
void DisableInterrupts(void);
void SetIntPrio(uint32_t PrioGroup,IRQn_Type IRQn,uint32_t prio);
void delay_us(uint16_t nus);
void delay_ms(uint16_t nms);

#endif
