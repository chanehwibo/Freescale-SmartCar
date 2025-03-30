#include "mk60_dma.h"
//超哥添加
//飞思卡尔MK60底层
//说明:dma底层

//dma初始化
//DMAx:DMA0,DMA1......
void dma_init(uint8_t DMAx,uint8_t Peripheral,uint32_t Source_Addr,uint8_t Source_Addr_inc,uint8_t Source_Addr_Adj,uint8_t Source_Size,
uint32_t Dest_Addr,uint8_t Dest_Addr_inc,uint8_t Dest_Addr_Adj,uint8_t Dest_Size,uint16_t Minor_loop_Length,uint32_t Trans_bytesNum,uint8_t AutoClose)
{
	SIM->SCGC6|=SIM_SCGC6_DMAMUX_MASK; //打开DMA多路复用器时钟
	SIM->SCGC7|=SIM_SCGC7_DMA_MASK;    //开启DMA时钟
	DMAMUX->CHCFG[DMAx]=DMAMUX_CHCFG_SOURCE(Peripheral); //设置通道Channelx的外设
//////////////////源地址相关//////////////////////////	
	DMA0->TCD[DMAx].SADDR=Source_Addr; //设置源地址
	DMA0->TCD[DMAx].SOFF=Source_Addr_inc; //源地址是否累加
	DMA0->TCD[DMAx].ATTR=0; //将数据长度寄存器清零
	DMA0->TCD[DMAx].SLAST=Source_Addr_Adj; //计数次数到达后是否改变源地址
  DMA0->TCD[DMAx].ATTR|=Source_Size; //源地址的传输宽度
//////////////////目的地址相关//////////////////////////
  DMA0->TCD[DMAx].DADDR=Dest_Addr; //设置目的地址
	DMA0->TCD[DMAx].DOFF=Dest_Addr_inc; //目的地址是否累加
	DMA0->TCD[DMAx].DLAST_SGA=Dest_Addr_Adj; //计数次数到达后是否改变目的地址
	DMA0->TCD[DMAx].ATTR|=Dest_Size; //目的地址的传输宽度	
	DMA0->TCD[DMAx].CITER_ELINKNO=DMA_CITER_ELINKNO_CITER(Minor_loop_Length); //设置数据长度,每次递减
	DMA0->TCD[DMAx].BITER_ELINKNO=DMA_BITER_ELINKNO_BITER(Minor_loop_Length); //起始循环计数器,主计数器为0时,装载
	DMA0->TCD[DMAx].NBYTES_MLNO=DMA_NBYTES_MLNO_NBYTES(Trans_bytesNum); //每次传输的字节数
	DMA0->TCD[DMAx].CSR=0; //清空CSR设置
	if(!DMA_INT) DMA0->INT&=~(1<<DMAx); //关闭相应通道中断请求
	else if(DMA_INT==1) 
	{
		DMA0->INT|=(1<<DMAx);  //开启相应通道中断请求 
		DMA0->TCD[DMAx].CSR|=DMA_CSR_INTHALF_MASK; //使能DMA主计数器减到一半时产生中断 
	}
  else if(DMA_INT==2) 
	{
		DMA0->INT|=(1<<DMAx);  //开启相应通道中断请求 
		DMA0->TCD[DMAx].CSR|=DMA_CSR_INTMAJOR_MASK; //使能DMA主计数器减到0时产生中断 
	}
	if(!AutoClose) 	DMA0->TCD[DMAx].CSR|=DMA_CSR_DREQ_MASK; //DMA主计数器减到0后,自动关闭DMA
	else
	{
	  DMA0->TCD[DMAx].CSR&=~(DMA_CSR_DREQ_MASK); //DMA主计数器减到0后,不关闭DMA	
	}
	DMAMUX->CHCFG[DMAx]|=DMAMUX_CHCFG_ENBL_MASK; //DMA通道使能
  DMA0->ERQ|=1<<DMAx; //开启通道x硬件DMA请求
}

