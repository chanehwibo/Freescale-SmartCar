#include "ov7725.h"
#include "control.h"
#include "oled.h"

//��ɽ�����

u8 Image_zip[ROW*COLUMN/8]; //ѹ������
u8 Image_Data[ROW][COLUMN]; //��ѹ����

//����ͷ�˿ڳ�ʼ��
//����0��ʼ���ɹ�
u8 OV7725_Init(void)
{
	u8 t;
	u16 id;
	IIC_Init();//�ȳ�ʼ��IIC
  id=Read_Reg(OV7725_ADDRESS,OV7725_PID);//��ȡOV7725�豸ID
	id=id<<8;
	id=id|Read_Reg(OV7725_ADDRESS,OV7725_VER);
	if(id==0X7721)//��ȡ�ɹ���
	{
		if(Write_Reg(OV7725_ADDRESS,   OV7725_COM7         , 0x80)==1) return 1;//��λ���мĴ���  
		if(Write_Reg(OV7725_ADDRESS,   OV7725_COM4         , 0x81)==1) return 1;  
    if(Write_Reg(OV7725_ADDRESS,   OV7725_CLKRC        , 0x00)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_COM2         , 0x03)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_COM3         , 0xD0)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_COM7         , 0x40)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_HSTART       , 0x3F)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_HSIZE        , 0x50)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_VSTRT        , 0x03)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_VSIZE        , 0x78)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_HREF         , 0x00)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_SCAL0        , 0x0A)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_AWB_Ctrl0    , 0xE0)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_DSPAuto      , 0xff)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_DSP_Ctrl2    , 0x0C)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_DSP_Ctrl3    , 0x00)==1) return 1;
    if(Write_Reg(OV7725_ADDRESS,   OV7725_DSP_Ctrl4    , 0x00)==1) return 1;
		//����ͼ����
		if(COLUMN==80)        {if(Write_Reg(OV7725_ADDRESS,  OV7725_HOutSize    , 0x14)==1) return 1;}
    else if(COLUMN==160)  {if(Write_Reg(OV7725_ADDRESS,  OV7725_HOutSize    , 0x28)==1) return 1;}
    else if(COLUMN==240)  {if(Write_Reg(OV7725_ADDRESS,  OV7725_HOutSize    , 0x3c)==1) return 1;}
    else if(COLUMN==320)  {if(Write_Reg(OV7725_ADDRESS,  OV7725_HOutSize    , 0x50)==1) return 1;}
    //����ͼ��߶�   
    if(ROW==60)           {if(Write_Reg(OV7725_ADDRESS,  OV7725_VOutSize    , 0x1E)==1) return 1;}
    else if(ROW==120)     {if(Write_Reg(OV7725_ADDRESS,  OV7725_VOutSize    , 0x3c)==1) return 1;}
    else if(ROW==180)     {if(Write_Reg(OV7725_ADDRESS,  OV7725_VOutSize    , 0x5a)==1) return 1;}
    else if(ROW==240)     {if(Write_Reg(OV7725_ADDRESS,  OV7725_VOutSize    , 0x78)==1) return 1;}
		
		if(Write_Reg(OV7725_ADDRESS,  OV7725_EXHCH       , 0x00)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM1        , 0x0c)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM2        , 0x16)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM3        , 0x2a)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM4        , 0x4e)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM5        , 0x61)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM6        , 0x6f)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM7        , 0x7b)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM8        , 0x86)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM9        , 0x8e)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM10       , 0x97)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM11       , 0xa4)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM12       , 0xaf)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM13       , 0xc5)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM14       , 0xd7)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_GAM15       , 0xe8)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_SLOP        , 0x20)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_LC_RADI     , 0x00)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_LC_COEF     , 0x13)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_LC_XC       , 0x08)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_LC_COEFB    , 0x14)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_LC_COEFR    , 0x17)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_LC_CTR      , 0x05)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_BDBase      , 0x99)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_BDMStep     , 0x03)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_SDE         , 0x04)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_BRIGHT      , 0x00)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_CNST        , 0x40)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_SIGN        , 0x06)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_UVADJ0      , 0x11)==1) return 1;
		if(Write_Reg(OV7725_ADDRESS,  OV7725_UVADJ1      , 0x02)==1) return 1;
    for(t=0;t<8;t++) gpio_init(PTD,t,0,PULL_UP); //��������������
		gpio_int_init(PTB,23,RISING,PULL_DOWN);      //���ж�������
	  gpio_int_init(PTC,6,DMA_FALLING,PULL_UP);    //����ͬ��ʱ��(�����½��ش���,����ᶪʧһ���ֽ�)
		NVIC_DisableIRQ(PORTC_IRQn);                 //������ʱ���ж�
		dma_gpio_to_buffer(DMA_Channel0,PORTC_DMAREQ,(u32)&PTD->PDIR,(u32)Image_zip,ROW*COLUMN/8); //��ʼ��DMA,�ش�������ж�,��DMA����,������ɺ��Զ��ر�DMA����
		return 0;	//��ʼ���ɹ�
	}
	else return 1; //��ʼ��ʧ��
}
//���жϺ���
void PORTB_IRQHandler(void)
{
  if(PORTB->ISFR&(1<<23))//���ж�
	{
		PORTB->ISFR|=1<<23; 
	  DMA_ResetDestAddress(DMA_Channel0,(u32)Image_zip); //�ָ�Ŀ���ַ
	}
}
//ͼ���ѹ
//resԴ��ַ desĿ�ĵ�ַ
void Image_Decompression(u8 *res,u8 *des)
{
    u8  temp[2]={255,0};
    u16 lenth=ROW*COLUMN/8;
    u8  i=8;
    while(lenth--)
    {
       i=8;
       while(i--)
       {
         *des++=temp[(*res>>i)&0x01];
       }
       res++;
    }
}
//��ʾͼ��
void Display_Image_On_PC(void)
{
	u16 i,j;
  uart_sendbyte(UART_Printf,0XFF); 
	for(i=0;i<ROW;i++)
	{
		for(j=0;j<COLUMN;j++)
		{
			if(j==left[i]||j==mid[i]||j==right[i]) uart_sendbyte(UART_Printf,150);
			else uart_sendbyte(UART_Printf,Image_Data[i][j]==0XFF?0XFE:0);
		}
	}	
}
//��OLED����ʾͼ��
void Display_Image_On_OLED(void)
{
	u16 i,j;
	for(i=0;i<60;i++)
	{
		for(j=0;j<80;j++)
		{
			if(j==mid[i]) OLED_DrawPoint(j+24,i+2,1);
			else OLED_DrawPoint(j+24,i+2,Image_Data[i][j]==0XFF?0:1);
		}
	}	
}
