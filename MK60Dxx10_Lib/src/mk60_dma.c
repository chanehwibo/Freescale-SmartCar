#include "mk60_dma.h"
//�������
//��˼����MK60�ײ�
//˵��:dma�ײ�

//dma��ʼ��
//DMAx:DMA0,DMA1......
void dma_init(uint8_t DMAx,uint8_t Peripheral,uint32_t Source_Addr,uint8_t Source_Addr_inc,uint8_t Source_Addr_Adj,uint8_t Source_Size,
uint32_t Dest_Addr,uint8_t Dest_Addr_inc,uint8_t Dest_Addr_Adj,uint8_t Dest_Size,uint16_t Minor_loop_Length,uint32_t Trans_bytesNum,uint8_t AutoClose)
{
	SIM->SCGC6|=SIM_SCGC6_DMAMUX_MASK; //��DMA��·������ʱ��
	SIM->SCGC7|=SIM_SCGC7_DMA_MASK;    //����DMAʱ��
	DMAMUX->CHCFG[DMAx]=DMAMUX_CHCFG_SOURCE(Peripheral); //����ͨ��Channelx������
//////////////////Դ��ַ���//////////////////////////	
	DMA0->TCD[DMAx].SADDR=Source_Addr; //����Դ��ַ
	DMA0->TCD[DMAx].SOFF=Source_Addr_inc; //Դ��ַ�Ƿ��ۼ�
	DMA0->TCD[DMAx].ATTR=0; //�����ݳ��ȼĴ�������
	DMA0->TCD[DMAx].SLAST=Source_Addr_Adj; //��������������Ƿ�ı�Դ��ַ
  DMA0->TCD[DMAx].ATTR|=Source_Size; //Դ��ַ�Ĵ�����
//////////////////Ŀ�ĵ�ַ���//////////////////////////
  DMA0->TCD[DMAx].DADDR=Dest_Addr; //����Ŀ�ĵ�ַ
	DMA0->TCD[DMAx].DOFF=Dest_Addr_inc; //Ŀ�ĵ�ַ�Ƿ��ۼ�
	DMA0->TCD[DMAx].DLAST_SGA=Dest_Addr_Adj; //��������������Ƿ�ı�Ŀ�ĵ�ַ
	DMA0->TCD[DMAx].ATTR|=Dest_Size; //Ŀ�ĵ�ַ�Ĵ�����	
	DMA0->TCD[DMAx].CITER_ELINKNO=DMA_CITER_ELINKNO_CITER(Minor_loop_Length); //�������ݳ���,ÿ�εݼ�
	DMA0->TCD[DMAx].BITER_ELINKNO=DMA_BITER_ELINKNO_BITER(Minor_loop_Length); //��ʼѭ��������,��������Ϊ0ʱ,װ��
	DMA0->TCD[DMAx].NBYTES_MLNO=DMA_NBYTES_MLNO_NBYTES(Trans_bytesNum); //ÿ�δ�����ֽ���
	DMA0->TCD[DMAx].CSR=0; //���CSR����
	if(!DMA_INT) DMA0->INT&=~(1<<DMAx); //�ر���Ӧͨ���ж�����
	else if(DMA_INT==1) 
	{
		DMA0->INT|=(1<<DMAx);  //������Ӧͨ���ж����� 
		DMA0->TCD[DMAx].CSR|=DMA_CSR_INTHALF_MASK; //ʹ��DMA������������һ��ʱ�����ж� 
	}
  else if(DMA_INT==2) 
	{
		DMA0->INT|=(1<<DMAx);  //������Ӧͨ���ж����� 
		DMA0->TCD[DMAx].CSR|=DMA_CSR_INTMAJOR_MASK; //ʹ��DMA������������0ʱ�����ж� 
	}
	if(!AutoClose) 	DMA0->TCD[DMAx].CSR|=DMA_CSR_DREQ_MASK; //DMA������������0��,�Զ��ر�DMA
	else
	{
	  DMA0->TCD[DMAx].CSR&=~(DMA_CSR_DREQ_MASK); //DMA������������0��,���ر�DMA	
	}
	DMAMUX->CHCFG[DMAx]|=DMAMUX_CHCFG_ENBL_MASK; //DMAͨ��ʹ��
  DMA0->ERQ|=1<<DMAx; //����ͨ��xӲ��DMA����
}

