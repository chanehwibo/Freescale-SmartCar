#include "mk60_spi.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:spi底层

//spi初始化
//SPIx:SPI0,SPI1,SPI2
//SPI_Prescaler:默认传输速度
void spi_init(SPI_Type *SPIx,uint8_t SPI_Prescaler)
{
	uint32_t SPI_Speed;
	switch((uint32_t)SPIx)
	{
		case SPI0_BASE:
		{
			SIM->SCGC6|=1<<12;
			if(SPI0_SCK==SPI_PA15)      gpio_alf_init(PTA,15,ALF2);
			else if(SPI0_SCK==SPI_PC5)  gpio_alf_init(PTC,5,ALF2);
			else if(SPI0_SCK==SPI_PD1)  gpio_alf_init(PTD,1,ALF2);
			if(SPI0_MOSI==SPI_PA16)     gpio_alf_init(PTA,16,ALF2);
			else if(SPI0_MOSI==SPI_PC6) gpio_alf_init(PTC,6,ALF2);
			else if(SPI0_MOSI==SPI_PD2) gpio_alf_init(PTD,2,ALF2);
			if(SPI0_MISO==SPI_PA17)     gpio_alf_init(PTA,17,ALF2);
			else if(SPI0_MISO==SPI_PC7) gpio_alf_init(PTC,7,ALF2);
			else if(SPI0_MISO==SPI_PD3) gpio_alf_init(PTD,3,ALF2);
			break;
		}
		case SPI1_BASE:
		{
			SIM->SCGC6|=1<<13;
			if(SPI1_SCK==SPI_PE2)         gpio_alf_init(PTE,2,ALF2);
			else if(SPI1_SCK==SPI_PB11)   gpio_alf_init(PTB,11,ALF2);
			if(SPI1_MOSI==SPI_PE1)        gpio_alf_init(PTE,1,ALF2);
			else if(SPI1_MOSI==SPI_PB16)  gpio_alf_init(PTB,16,ALF2);
			if(SPI1_MISO==SPI_PE3)        gpio_alf_init(PTE,3,ALF2);
			else if(SPI1_MISO==SPI_PB17)  gpio_alf_init(PTB,17,ALF2);
		  break;
		}
		case SPI2_BASE:
		{
			SIM->SCGC3|=1<<12;
			if(SPI2_SCK==SPI_PB21)        gpio_alf_init(PTB,21,ALF2);
			else if(SPI2_SCK==SPI_PD12)   gpio_alf_init(PTD,12,ALF2);
			if(SPI2_MOSI==SPI_PB22)       gpio_alf_init(PTB,22,ALF2);
			else if(SPI2_MOSI==SPI_PD13)  gpio_alf_init(PTD,13,ALF2);
			if(SPI2_MISO==SPI_PB23)       gpio_alf_init(PTB,23,ALF2);
			else if(SPI2_MISO==SPI_PD14)  gpio_alf_init(PTD,14,ALF2);
			break;
		}
		default:break;
	}
	SPIx->MCR=(0|SPI_MCR_CLR_TXF_MASK|SPI_MCR_CLR_RXF_MASK|SPI_MCR_HALT_MASK);
	SPIx->SR=(0|SPI_SR_EOQF_MASK|SPI_SR_TFUF_MASK|SPI_SR_TFFF_MASK|SPI_SR_RFOF_MASK|SPI_SR_RFDF_MASK);
	SPIx->MCR=(0|SPI_MCR_MSTR_MASK|SPI_MCR_PCSIS(0)|SPI_MCR_PCSIS_MASK);
	SPIx->CTAR[0]&=0X07FCFFF0;//清除DBR,FMSZ,PBR,BR
	SPI_Speed=0XB8000000|SPI_Prescaler;
	SPIx->CTAR[0]|=SPI_Speed;
	SPIx->MCR&=~SPI_MCR_HALT_MASK;
}
//设置SPI传输速度
//SPIx:SPI0,SPI1,SPI2
//SPI_Prescaler:传输速度
//SPI速度=SystemClock*(1+DBR)/PBR/BR
void SPI_SetSpeed(SPI_Type *SPIx,uint8_t SPI_Prescaler)
{
	uint32_t SPI_Speed;
	SPIx->CTAR[0]&=0X07FCFFF0;//清除DBR,FMSZ,PBR,BR
	SPI_Speed=0XB8000000|SPI_Prescaler;
	SPIx->CTAR[0]|=SPI_Speed;
	SPIx->MCR&=~SPI_MCR_HALT_MASK;
}
//发送接收一个字节
//SPIx:SPI0,SPI1,SPI2
//data:数据
uint8_t SPIx_WriteReadByte(SPI_Type *SPIx,uint8_t data)
{
	do
	{
		SPIx->SR=(0|SPI_SR_EOQF_MASK|SPI_SR_TFUF_MASK|SPI_SR_TFFF_MASK|SPI_SR_RFOF_MASK|SPI_SR_RFDF_MASK);
		SPIx->MCR|=(0|SPI_MCR_CLR_TXF_MASK|SPI_MCR_CLR_RXF_MASK);
	}
	while((SPIx->SR&SPI_SR_RFDF_MASK)); 
	SPIx->PUSHR=(0|SPI_PUSHR_CTAS(0)|SPI_PUSHR_EOQ_MASK|SPI_PUSHR_TXDATA(data));
	while((SPIx->SR&SPI_SR_EOQF_MASK)==0);          
	while(!(SPIx->SR&SPI_SR_RFDF_MASK));           
	data=SPIx->POPR;                  
	SPIx->SR|=SPI_SR_RFDF_MASK;
	return data;
}
