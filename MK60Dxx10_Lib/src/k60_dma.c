#include "k60_dma.h"
//��ɽ�����
//��˼����MK60�ײ�
//˵��:dma�ײ�

//����DMA�����Դ��ַ���
//DMA_Channel:DMAͨ��,DMA_Channel0~DMA_Channel15
//Source_Address:Դ��ַ
//Ssize:Դ��ַ�Ĵ�����(0:8bit,1:16bit,2:32bit,4:16byte)
//Soff:Դ��ַ������
//Slast:���������Դ��ַ������
void dma_set_source_about(unsigned char DMA_Channel,u32 Source_Address,unsigned char Ssize,unsigned short Soff,unsigned int Slast)
{
	DMA0->TCD[DMA_Channel].SADDR=Source_Address; //����Դ��ַ
	DMA0->TCD[DMA_Channel].SOFF=Soff;            //Դ��ַ������
	DMA0->TCD[DMA_Channel].ATTR&=~(unsigned short)(0XFF<<8);//���SMOD��SSIZE
	DMA0->TCD[DMA_Channel].ATTR|=Ssize<<8;       //���ô�����
	DMA0->TCD[DMA_Channel].SLAST=Slast;          //�������������Դ��ַ������
}
//����DMA�����Ŀ���ַ���
//DMA_Channel:DMAͨ��,DMA_Channel0~DMA_Channel15
//Dest_Address:Ŀ���ַ
//Dsize:Ŀ���ַ�Ĵ�����(0:8bit,1:16bit,2:32bit,4:16byte)
//Doff:Ŀ���ַ�Լ���
//Dlast:���������Ŀ���ַ������
void dma_set_dest_about(unsigned char DMA_Channel,unsigned int Dest_Address,unsigned char Dsize,unsigned short Doff,unsigned int Dlast)
{
	DMA0->TCD[DMA_Channel].DADDR=Dest_Address;  //����Ŀ���ַ
	DMA0->TCD[DMA_Channel].DOFF=Doff;           //Ŀ���ַ������
	DMA0->TCD[DMA_Channel].ATTR&=~(unsigned short)0XFF;    //���DMOD��DSIZE
	DMA0->TCD[DMA_Channel].ATTR|=Dsize;         //���ô�����(0:8bit,1:16bit,2:32bit,4:16byte)
	DMA0->TCD[DMA_Channel].DLAST_SGA=Dlast;     //����������Ŀ�ĵ�ַ������
}
//����DMAͨ�������ȼ�
//DMA_Channel:DMAͨ��,DMA_Channel0~DMA_Channel15
//BeSuspend:�ܷ񱻸����ȼ���DMAͨ�����,0�ܱ���������ʱ���,1�������ȴ��
//Prio:DMAͨ�����ȼ�(0~15)
void dma_set_prio(unsigned char DMA_Channel,unsigned char BeSuspend,unsigned char Prio)
{
	unsigned int PrioRegAddr; //���ȼ��Ĵ�����ַ
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
	*(vu32 *)PrioRegAddr=0X00; //��Ĵ���ֵ
	if(BeSuspend) *(vu32 *)PrioRegAddr&=~(1<<7); //�������ȵĴ��
	else *(vu32 *)PrioRegAddr|=1<<7; //�ܱ���������ʱ���
	*(vu32 *)PrioRegAddr&=~(1<<6); //���Դ�ϵ����ȼ���ͨ��
	*(vu32 *)PrioRegAddr|=Prio&0XF; //д�����ȼ�ֵ
}
//��ʼ��DMA
//DMA_Channel:DMAͨ��,DMA_Channel0~DMA_Channel15
//Periph:DMA������
//DmaTransNums:���˴���
//Bytes:ÿ�δ�����ֽ���
//AutoClose:1������ɺ�ر�DMA����,0������ɺ󲻹ر�DMA����
//DmaInt:1������������ж�,0�رմ�������ж�
//DmaDreqEn:1����DMAͨ������,0�ر�DMAͨ������
void dma_init(unsigned char DMA_Channel,unsigned char Periph,unsigned short DmaTransNums,unsigned int Bytes,unsigned char AutoClose,unsigned char DmaInt,unsigned char DmaDreqEn)
{
	SIM->SCGC6|=1<<1; //��DMA��·������ʱ��
	SIM->SCGC7|=1<<1; //����DMAʱ��
	DMAMUX->CHCFG[DMA_Channel]=Periph; //����ͨ��Channelx������
	DMA0->TCD[DMA_Channel].CITER_ELINKNO=DmaTransNums&0X7FFF; //�������ݳ���,ÿ�εݼ�
	DMA0->TCD[DMA_Channel].BITER_ELINKNO=DmaTransNums&0X7FFF; //��ʼѭ��������,��������Ϊ0ʱ,����װ�ؼ���ֵ
	DMA0->TCD[DMA_Channel].NBYTES_MLNO=Bytes; //ÿ�δ�����ֽ���
	DMA0->TCD[DMA_Channel].CSR=0; //���CSR����
	DMA0->TCD[DMA_Channel].CSR|=AutoClose<<3; //��������Ƿ�ر�DMA����
	if(DmaInt) 
	{
		DMA0->TCD[DMA_Channel].CSR|=1<<1; //������������0�����ж�
		NVIC_EnableIRQ((IRQn_Type)DMA_Channel);//���ں��ж�
	}
	else 
	{
		DMA0->TCD[DMA_Channel].CSR&=~(1<<1); //������������0�������ж�
		NVIC_DisableIRQ((IRQn_Type)DMA_Channel); //���ں��ж�
	}
	DMAMUX->CHCFG[DMA_Channel]|=1<<7; //DMAͨ��ʹ��
	if(DmaDreqEn) DMA0->ERQ|=1<<DMA_Channel; //����DMAͨ������
	else DMA0->ERQ&=~(1<<DMA_Channel); //�ر�DMAͨ������
}
//��������ͷDMA�ɼ�
//DMA_Channel:DMAͨ��,DMA_Channel0~DMA_Channel15
//Periph:PCLKʱ�ӵ�DMA������
//Source_Address:Դ��ַ
//Dest_Address:Ŀ���ַ
//DmaTransNums:���˴���
void dma_gpio_to_buffer(unsigned char DMA_Channel,unsigned char Periph,unsigned int Source_Address,unsigned int Dest_Address,unsigned short DmaTransNums)
{
	dma_set_source_about(DMA_Channel,Source_Address,0,0,0); 
	dma_set_dest_about(DMA_Channel,Dest_Address,0,1,0); 
	dma_init(DMA_Channel,Periph,DmaTransNums,1,0,0,1); //Ĭ�Ͽ���DMA����,�ر�DMA�ж�,������ɺ󲻹ر�DMA����
}
//IO��DMA��ʽ����,��ռ��CPU��Դ
//DMA_Channel:DMAͨ��,DMA_Channel0~DMA_Channel15
//GPIOx:PTA,PTB...
//n:���ű��
//mode:�ж�ģʽ,ֻ����DMA_RISING��DMA_FALLING
//pull:��������ѡ��
void dma_gpio_counter_init(unsigned char DMA_Channel,GPIO_Type *GPIOx,unsigned char n,unsigned char mode,unsigned char pull)
{
	gpio_int_init(GPIOx,n,mode,pull); //��ʼ��IO
	dma_set_source_about(DMA_Channel,0XFFFFFFFF,0,0,0); //Դ��ַΪ��Чֵ
	dma_set_dest_about(DMA_Channel,0XFFFFFFFF,0,0,0); //Ŀ���ַΪ��Чֵ
	switch((u32)(GPIOx)) //��ʼ��DMA����,����DMA����
	{
		case PTA_BASE:dma_init(DMA_Channel,PORTA_DMAREQ,30000,1,0,0,1);break;
		case PTB_BASE:dma_init(DMA_Channel,PORTB_DMAREQ,30000,1,0,0,1);break;
		case PTC_BASE:dma_init(DMA_Channel,PORTC_DMAREQ,30000,1,0,0,1);break;
		case PTD_BASE:dma_init(DMA_Channel,PORTD_DMAREQ,30000,1,0,0,1);break;
		case PTE_BASE:dma_init(DMA_Channel,PORTE_DMAREQ,30000,1,0,0,1);break;
		default:break;
	}
}
//��ȡ������ֵ
//DMA_Channel:DMAͨ��,DMA_Channel0~DMA_Channel15
unsigned short dma_get_counter(unsigned char DMA_Channel)
{
	unsigned short data;
	data=DMA0->TCD[DMA_Channel].CITER_ELINKNO; 
	DMA0->TCD[DMA_Channel].CITER_ELINKNO=30000; //���¼���
	return(30000-data); //���ֵ
}
