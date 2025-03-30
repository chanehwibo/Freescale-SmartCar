#include "iic.h"
//��ɽ�����
//IIC��ʼ��
void IIC_Init(void)
{
	gpio_init(PTE,10,1,PULL_UP); 		//SCL//gpio_init(PTE,24,1,PULL_UP); //SCL
	gpio_init(PTE,11,1,PULL_UP);		//gpio_init(PTE,26,1,PULL_UP); //SDA
	IIC_Stop();//��ֹͣIIC
	SDA_H;
	SCL_H;
	delay_ms(100);
}
//����һ�������ź�
void IIC_Start(void)
{
  SDA_H;
	SCL_H;
	delay_us(4);
	SDA_L;
	delay_us(4);
	SCL_L; //��SCL�õ�,�������ݴ���
	delay_us(4);
}
//����һ��ֹͣ�ź�
void IIC_Stop(void)
{
	SDA_L;
	SCL_H; //��SCL�ø�,��ֹ���ݴ���
	delay_us(4);
  SDA_H;
}
//��ӻ�����һ���ֽ�����
//��λ��ǰ
void IIC_SendByte(u8 data)
{
	u8 i;
  for(i=0;i<8;i++)
	{		
		if(data&0x80)
		{
			SDA_H;
		}
		else
		{
			SDA_L;
		}
		delay_us(4);
		SCL_H;
		delay_us(4);	
		SCL_L;
		if(i==7)
		{
			SDA_H;  //�ͷ�����
		}
		data<<=1;	//����һ��bit
		delay_us(4);
	}
}
//��ȡһ���ֽ�
u8 IIC_ReadByte(void)
{
	u8 i;
	u8 value;
  //������1��bitΪ���ݵ�bit7
	value =0;
	SDA_IN;
	for(i=0;i<8;i++)
	{
		value<<=1;
		SCL_H;
		delay_us(4);
		if(READ_SDA)
		{
			value++;
		}
		SCL_L;
		delay_us(4);
	}
	SDA_OUT;
	return value;
}
//�ȴ�Ӧ��
u8 IIC_WaitAck(void)
{
	u8 re;
  SDA_H;	 //CPU�ͷ�SDA���� 
	delay_us(4);
	SCL_H;	 //CPU����SCL=1,��ʱ�����᷵��ACKӦ�� 
	delay_us(4);
	SDA_IN;
	if(READ_SDA)	//CPU��ȡSDA����״̬ 
	{
		re=1;
	}
	else
	{
		re=0;
	}
	SDA_OUT;
	SCL_L;
	delay_us(4);
	return re;
}
//����Ӧ���ź�
void IIC_Ack(void)
{
	SDA_L;	//CPU����SDA=0 
	delay_us(4);
	SCL_H;	//CPU����1��ʱ��
	delay_us(4);
	SCL_L;
	delay_us(4);
	SDA_H;	//CPU�ͷ�SDA����
}
//������Ӧ���ź�
void IIC_NAck(void)
{
	SDA_H;	
	delay_us(4);
	SCL_H;	
	delay_us(4);
	SCL_L;
	delay_us(4);
}
//д�Ĵ���
//�������ɹ�������ѭ��
u8 Write_Reg(u8 device,u8 reg,u8 data)
{
	IIC_Start();
	IIC_SendByte(device);
	if(IIC_WaitAck()!=0) return 1;
	IIC_SendByte(reg);
	if(IIC_WaitAck()!=0) return 1;
	IIC_SendByte(data);
  if(IIC_WaitAck()!=0) return 1;
	IIC_Stop();
	delay_ms(5); //��ʱ�ȴ�д��ɹ�
	return 0;
}
//���Ĵ���
//�������ɹ�������ѭ��
u8 Read_Reg(u8 device,u8 reg)
{
	u8 data;
  IIC_Start();
	IIC_SendByte(device);
	if(IIC_WaitAck()!=0)
	{
		while(1);
	}
	IIC_SendByte(reg);
	if(IIC_WaitAck()!=0)
	{
		while(1);
	}
	IIC_Stop();
	IIC_Start();
	IIC_SendByte(device+1);
	if(IIC_WaitAck()!=0)
	{
		while(1);
	}
	data=IIC_ReadByte();
	IIC_Stop();
  return data;
}
