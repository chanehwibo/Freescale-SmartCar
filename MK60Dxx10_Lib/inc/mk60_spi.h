#ifndef _MK60_SPI_H
#define _MK60_SPI_H
#include "mk60_gpio.h"
#include "mk60_sys.h"
//��ɽ�����
//��˼����MK60�ײ�
//˵��:spi�ײ�
 
//SPI�����ٶ�
typedef enum
{
	SPI_Prescaler_2=0,
	SPI_Prescaler_4,
  SPI_Prescaler_6,
	SPI_Prescaler_8,
  SPI_Prescaler_16,
	SPI_Prescaler_32, 
	SPI_Prescaler_64, 
  SPI_Prescaler_128,
	SPI_Prescaler_256, 
  SPI_Prescaler_512,
  SPI_Prescaler_1024,	
	SPI_Prescaler_2048,
	SPI_Prescaler_4096,
	SPI_Prescaler_8192,
	SPI_Prescaler_16384,
	SPI_Prescaler_32768,
}SPI_Speed;
//SPI�ܽ�
typedef enum
{
////SPI0�ܽ�//////
	SPI_PA15=0,//SPI0_SCK
	SPI_PA16,//SPI0_MOSI
	SPI_PA17,//SPI0_MISO
	SPI_PC5,//SPI0_SCK
	SPI_PC6,//SPI0_MOSI
	SPI_PC7,//SPI0_MISO
	SPI_PD1,//SPI0_SCK
	SPI_PD2,//SPI0_MOSI
	SPI_PD3,//SPI0_MISO
////SPI1�ܽ�//////
  SPI_PE2,//SPI1_SCK
	SPI_PE1,//SPI1_MOSI
	SPI_PE3,//SPI1_MISO
	SPI_PB11,//SPI1_SCK
	SPI_PB16,//SPI1_MOSI
	SPI_PB17,//SPI1_MISO
////SPI2�ܽ�//////
  SPI_PB21,//SPI2_SCK
	SPI_PB22,//SPI2_MOSI
	SPI_PB23,//SPI2_MISO	
	SPI_PD12,//SPI2_SCK
	SPI_PD13,//SPI2_MOSI
	SPI_PD14,//SPI2_MISO
}SPI_Pin;

//spi�⺯��
void spi_init(SPI_Type *SPIx,uint8_t SPI_Prescaler);
void SPI_SetSpeed(SPI_Type *SPIx,uint8_t SPI_Prescaler);
uint8_t SPIx_WriteReadByte(SPI_Type *SPIx,uint8_t data);

#endif
