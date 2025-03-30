#ifndef _MK60_DMA_H
#define _MK60_DMA_H
#include "mk60_sys.h"
//超哥添加
//飞思卡尔MK60底层
//说明:dma底层

//DMA外设请求号
#define PORTA_DMAREQ  49
#define PORTB_DMAREQ  50
#define PORTC_DMAREQ  51
#define PORTD_DMAREQ  52
#define PORTE_DMAREQ  53

//DMA通道
typedef enum
{
	DMA_Channel0,
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
//DMA通道申请
#define DMA_EN(DMAx)   DMA0->ERQ|=1<<DMAx
#define DMA_DIS(DMAx)  DMA0->ERQ&=~(1<<DMAx)
void dma_init(uint8_t DMAx,uint8_t Peripheral,uint32_t Source_Addr,uint8_t Source_Addr_inc,uint8_t Source_Addr_Adj,uint8_t Source_Size,
uint32_t Dest_Addr,uint8_t Dest_Addr_inc,uint8_t Dest_Addr_Adj,uint8_t Dest_Size,uint16_t Minor_loop_Length,uint32_t Trans_bytesNum,uint8_t AutoClose);
#endif
