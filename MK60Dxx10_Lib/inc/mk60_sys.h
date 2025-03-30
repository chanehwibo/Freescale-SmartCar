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
//火山灰添加
//飞思卡尔MK60底层
//说明:系统时钟初始化底层
//数据类型
#ifndef u8
#define u8  uint8_t 
#endif
#ifndef u16
#define u16 uint16_t 
#endif
#ifndef u32
#define u32 uint32_t 
#endif

//系统时钟定义
#define ExternalClock  50  //晶振频率,必须为5的倍数,不能太大
#define PllClock       150 //锁相环输出时钟 (120Mhz~275Mhz)必须为5的倍数
#define SystemClock    150 //系统时钟(能被PllClock除尽,除的结果不大于16)
#define BusClock       150 //总线时钟(能被PllClock除尽,除的结果不大于16)
#define FlexClock      15  //FlexClock时钟(能被PllClock除尽,除的结果不大于16)
#define FlashClock     10  //FlashClock时钟(能被PllClock除尽,除的结果不大于16)

/////////////////////功能引脚选择//////////////////////

//UART模块
#define USE_RX   0//接收关闭
#define UART_TX  UART_PE24//TXD和RXD选择
#define UART_RX  UART_PE25
#define UART_Printf UART4

//SPI模块
#define SPI0_SCK   SPI_PA15 //SPI0引脚
#define SPI0_MOSI  SPI_PA16 
#define SPI0_MISO  SPI_PA17 
#define SPI1_SCK   SPI_PE2 //SPI1引脚
#define SPI1_MOSI  SPI_PE1
#define SPI1_MISO  SPI_PE3 
#define SPI2_SCK   SPI_PB21 //SPI2引脚
#define SPI2_MOSI  SPI_PB22
#define SPI2_MISO  SPI_PB23 

//FTM模块
#define FTM0_CLK_DIVIDE  ftm_clk_divide4 //FTM0时钟分频  
#define FTM1_CLK_DIVIDE  ftm_clk_divide64 //FTM1时钟分频  
#define FTM2_CLK_DIVIDE  ftm_clk_divide64 //FTM2时钟分频 
#define FTM0_CH0   FTM_PC1//FTM0 7个通道引脚设置
#define FTM0_CH1   FTM_PC2
#define FTM0_CH2   FTM_PC3
#define FTM0_CH3   FTM_PC4
#define FTM0_CH4   FTM_PA7
#define FTM0_CH5   FTM_PA0
#define FTM0_CH6   FTM_PA1
#define FTM0_CH7   FTM_PA2
#define FTM1_CH0   FTM_PA12//FTM1 2个通道引脚设置
#define FTM1_CH1   FTM_PA13
#define FTM2_CH0   FTM_PA10//FTM2 2个通道引脚设置
#define FTM2_CH1   FTM_PA11

//ADC模块
//到mk60_adc.h中查看

//LPTMR模块
#define LPTMR_COUNTER_PIN  LPTMR_PC5//可选(PC5,PA19)

//DMA模块
#define DMA_INT 0//关闭DMA中断
////////////////////////////////////////////////////////

//系统函数
void SystemInit(void);
void EnableInterrupts(void);
void DisableInterrupts(void);
void SetIntPrio(uint32_t PrioGroup,IRQn_Type IRQn,uint32_t prio);
void delay_us(uint16_t nus);
void delay_ms(uint16_t nms);

#endif
