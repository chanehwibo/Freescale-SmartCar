#ifndef _IIC_H
#define _IIC_H
#include "mk60_sys.h"
//»ðÉ½»ÒÌí¼Ó
#define  SDA_IN     PTE->PDDR&=~(1<<11);
#define  SDA_OUT    PTE->PDDR|=1<<11;
#define  SCL_H     PTE->PDOR|=1<<10;
#define  SCL_L     PTE->PDOR&=~(1<<10);
#define  SDA_H     PTE->PDOR|=1<<11;
#define  SDA_L     PTE->PDOR&=~(1<<11);
#define  READ_SDA  PTE->PDIR&(1<<11)

void IIC_Init(void);
void IIC_Start(void);
void IIC_Stop(void);
void IIC_SendByte(u8 data);
u8 IIC_ReadByte(void);
u8 IIC_WaitAck(void);
void IIC_Ack(void);
void IIC_NAck(void);
u8 Write_Reg(u8 device,u8 reg,u8 data);
u8 Read_Reg(u8 device,u8 reg);
#endif

