#include "k60_dma.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:dma底层

//设置DMA传输的源地址相关
//DMA_Channel:DMA通道,DMA_Channel0~DMA_Channel15
//Source_Address:源地址
//Ssize:源地址的传输宽度(0:8bit,1:16bit,2:32bit,4:16byte)
//Soff:源地址自增数
//Slast:传输结束后源地址调整量
void dma_set_source_about(unsigned char DMA_Channel,u32 Source_Address,unsigned char Ssize,unsigned short Soff,unsigned int Slast)
{
	DMA0->TCD[DMA_Channel].SADDR=Source_Address; //设置源地址
	DMA0->TCD[DMA_Channel].SOFF=Soff;            //源地址自增数
	DMA0->TCD[DMA_Channel].ATTR&=~(unsigned short)(0XFF<<8);//清除SMOD和SSIZE
	DMA0->TCD[DMA_Channel].ATTR|=Ssize<<8;       //设置传输宽度
	DMA0->TCD[DMA_Channel].SLAST=Slast;          //计数次数到达后源地址调整量
}
//设置DMA传输的目标地址相关
//DMA_Channel:DMA通道,DMA_Channel0~DMA_Channel15
//Dest_Address:目标地址
//Dsize:目标地址的传输宽度(0:8bit,1:16bit,2:32bit,4:16byte)
//Doff:目标地址自加数
//Dlast:传输结束后目标地址调整量
void dma_set_dest_about(unsigned char DMA_Channel,unsigned int Dest_Address,unsigned char Dsize,unsigned short Doff,unsigned int Dlast)
{
	DMA0->TCD[DMA_Channel].DADDR=Dest_Address;  //设置目标地址
	DMA0->TCD[DMA_Channel].DOFF=Doff;           //目标地址自增数
	DMA0->TCD[DMA_Channel].ATTR&=~(unsigned short)0XFF;    //清除DMOD和DSIZE
	DMA0->TCD[DMA_Channel].ATTR|=Dsize;         //设置传输宽度(0:8bit,1:16bit,2:32bit,4:16byte)
	DMA0->TCD[DMA_Channel].DLAST_SGA=Dlast;     //计数次数到目的地址调整量
}
//设置DMA通道的优先级
//DMA_Channel:DMA通道,DMA_Channel0~DMA_Channel15
//BeSuspend:能否被高优先级的DMA通道打断,0能被高优先暂时打断,1被高优先打断
//Prio:DMA通道优先级(0~15)
void dma_set_prio(unsigned char DMA_Channel,unsigned char BeSuspend,unsigned char Prio)
{
	unsigned int PrioRegAddr; //优先级寄存器地址
	switch(DMA_Channel)
	{
		case 0:PrioRegAddr=(u32)DMA0->DCHPRI0;break;
		case 1:PrioRegAddr=(u32)DMA0->DCHPRI1;break;
		case 2:PrioRegAddr=(u32)DMA0->DCHPRI2;break;
		case 3:PrioRegAddr=(u32)DMA0->DCHPRI3;break;	
		case 4:PrioRegAddr=(u32)DMA0->DCHPRI4;break;
		case 5:PrioRegAddr=(u32)DMA0->DCHPRI5;break;
		case 6:PrioRegAddr=(u32)DMA0->DCHPRI6;break;
		case 7:PrioRegAddr=(u32)DMA0->DCHPRI7;break;
		case 8:PrioRegAddr=(u32)DMA0->DCHPRI8;break;
		case 9:PrioRegAddr=(u32)DMA0->DCHPRI9;break;
		case 10:PrioRegAddr=(u32)DMA0->DCHPRI10;break;
		case 11:PrioRegAddr=(u32)DMA0->DCHPRI11;break;
		case 12:PrioRegAddr=(u32)DMA0->DCHPRI12;break;
		case 13:PrioRegAddr=(u32)DMA0->DCHPRI13;break;
		case 14:PrioRegAddr=(u32)DMA0->DCHPRI14;break;
		case 15:PrioRegAddr=(u32)DMA0->DCHPRI15;break;
		default: break;
	}	
	*(vu32 *)PrioRegAddr=0X00; //清寄存器值
	if(BeSuspend) *(vu32 *)PrioRegAddr&=~(1<<7); //被高优先的打断
	else *(vu32 *)PrioRegAddr|=1<<7; //能被高优先暂时打断
	*(vu32 *)PrioRegAddr&=~(1<<6); //可以打断低优先级的通道
	*(vu32 *)PrioRegAddr|=Prio&0XF; //写入优先级值
}
//初始化DMA
//DMA_Channel:DMA通道,DMA_Channel0~DMA_Channel15
//Periph:DMA外设编号
//DmaTransNums:搬运次数
//Bytes:每次传输的字节数
//AutoClose:1传输完成后关闭DMA请求,0传输完成后不关闭DMA请求
//DmaInt:1开启传输完成中断,0关闭传输完成中断
//DmaDreqEn:1开启DMA通道请求,0关闭DMA通道请求
void dma_init(unsigned char DMA_Channel,unsigned char Periph,unsigned short DmaTransNums,unsigned int Bytes,unsigned char AutoClose,unsigned char DmaInt,unsigned char DmaDreqEn)
{
	SIM->SCGC6|=1<<1; //打开DMA多路复用器时钟
	SIM->SCGC7|=1<<1; //开启DMA时钟
	DMAMUX->CHCFG[DMA_Channel]=Periph; //设置通道Channelx的外设
	DMA0->TCD[DMA_Channel].CITER_ELINKNO=DmaTransNums&0X7FFF; //设置数据长度,每次递减
	DMA0->TCD[DMA_Channel].BITER_ELINKNO=DmaTransNums&0X7FFF; //起始循环计数器,主计数器为0时,重新装载计数值
	DMA0->TCD[DMA_Channel].NBYTES_MLNO=Bytes; //每次传输的字节数
	DMA0->TCD[DMA_Channel].CSR=0; //清空CSR设置
	DMA0->TCD[DMA_Channel].CSR|=AutoClose<<3; //传输完成是否关闭DMA请求
	if(DmaInt) 
	{
		DMA0->TCD[DMA_Channel].CSR|=1<<1; //主计数器减到0产生中断
		NVIC_EnableIRQ((IRQn_Type)DMA_Channel);//开内核中断
	}
	else 
	{
		DMA0->TCD[DMA_Channel].CSR&=~(1<<1); //主计数器减到0不产生中断
		NVIC_DisableIRQ((IRQn_Type)DMA_Channel); //关内核中断
	}
	DMAMUX->CHCFG[DMA_Channel]|=1<<7; //DMA通道使能
	if(DmaDreqEn) DMA0->ERQ|=1<<DMA_Channel; //开启DMA通道请求
	else DMA0->ERQ&=~(1<<DMA_Channel); //关闭DMA通道请求
}
//数字摄像头DMA采集
//DMA_Channel:DMA通道,DMA_Channel0~DMA_Channel15
//Periph:PCLK时钟的DMA外设编号
//Source_Address:源地址
//Dest_Address:目标地址
//DmaTransNums:搬运次数
void dma_gpio_to_buffer(unsigned char DMA_Channel,unsigned char Periph,unsigned int Source_Address,unsigned int Dest_Address,unsigned short DmaTransNums)
{
	dma_set_source_about(DMA_Channel,Source_Address,0,0,0); 
	dma_set_dest_about(DMA_Channel,Dest_Address,0,1,0); 
	dma_init(DMA_Channel,Periph,DmaTransNums,1,0,0,1); //默认开启DMA请求,关闭DMA中断,传输完成后不关闭DMA请求
}
//IO口DMA方式计数,不占用CPU资源
//DMA_Channel:DMA通道,DMA_Channel0~DMA_Channel15
//GPIOx:PTA,PTB...
//n:引脚编号
//mode:中断模式,只能是DMA_RISING和DMA_FALLING
//pull:上拉下拉选择
void dma_gpio_counter_init(unsigned char DMA_Channel,GPIO_Type *GPIOx,unsigned char n,unsigned char mode,unsigned char pull)
{
	gpio_int_init(GPIOx,n,mode,pull); //初始化IO
	dma_set_source_about(DMA_Channel,0XFFFFFFFF,0,0,0); //源地址为无效值
	dma_set_dest_about(DMA_Channel,0XFFFFFFFF,0,0,0); //目标地址为无效值
	switch((u32)(GPIOx)) //初始化DMA外设,开启DMA请求
	{
		case PTA_BASE:dma_init(DMA_Channel,PORTA_DMAREQ,30000,1,0,0,1);break;
		case PTB_BASE:dma_init(DMA_Channel,PORTB_DMAREQ,30000,1,0,0,1);break;
		case PTC_BASE:dma_init(DMA_Channel,PORTC_DMAREQ,30000,1,0,0,1);break;
		case PTD_BASE:dma_init(DMA_Channel,PORTD_DMAREQ,30000,1,0,0,1);break;
		case PTE_BASE:dma_init(DMA_Channel,PORTE_DMAREQ,30000,1,0,0,1);break;
		default:break;
	}
}
//获取计数器值
//DMA_Channel:DMA通道,DMA_Channel0~DMA_Channel15
unsigned short dma_get_counter(unsigned char DMA_Channel)
{
	unsigned short data;
	data=DMA0->TCD[DMA_Channel].CITER_ELINKNO; 
	DMA0->TCD[DMA_Channel].CITER_ELINKNO=30000; //重新计数
	return(30000-data); //求差值
}
