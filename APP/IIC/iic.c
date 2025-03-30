#include "iic.h"
//火山灰添加
//IIC初始化
void IIC_Init(void)
{
	gpio_init(PTE,10,1,PULL_UP); 		//SCL//gpio_init(PTE,24,1,PULL_UP); //SCL
	gpio_init(PTE,11,1,PULL_UP);		//gpio_init(PTE,26,1,PULL_UP); //SDA
	IIC_Stop();//先停止IIC
	SDA_H;
	SCL_H;
	delay_ms(100);
}
//产生一个启动信号
void IIC_Start(void)
{
  SDA_H;
	SCL_H;
	delay_us(4);
	SDA_L;
	delay_us(4);
	SCL_L; //将SCL置低,启动数据传输
	delay_us(4);
}
//产生一个停止信号
void IIC_Stop(void)
{
	SDA_L;
	SCL_H; //将SCL置高,终止数据传输
	delay_us(4);
  SDA_H;
}
//向从机发送一个字节数据
//高位在前
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
			SDA_H;  //释放总线
		}
		data<<=1;	//左移一个bit
		delay_us(4);
	}
}
//读取一个字节
u8 IIC_ReadByte(void)
{
	u8 i;
	u8 value;
  //读到第1个bit为数据的bit7
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
//等待应答
u8 IIC_WaitAck(void)
{
	u8 re;
  SDA_H;	 //CPU释放SDA总线 
	delay_us(4);
	SCL_H;	 //CPU驱动SCL=1,此时器件会返回ACK应答 
	delay_us(4);
	SDA_IN;
	if(READ_SDA)	//CPU读取SDA口线状态 
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
//产生应答信号
void IIC_Ack(void)
{
	SDA_L;	//CPU驱动SDA=0 
	delay_us(4);
	SCL_H;	//CPU产生1个时钟
	delay_us(4);
	SCL_L;
	delay_us(4);
	SDA_H;	//CPU释放SDA总线
}
//产生非应答信号
void IIC_NAck(void)
{
	SDA_H;	
	delay_us(4);
	SCL_H;	
	delay_us(4);
	SCL_L;
	delay_us(4);
}
//写寄存器
//操作不成功进入死循环
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
	delay_ms(5); //延时等待写入成功
	return 0;
}
//读寄存器
//操作不成功进入死循环
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
