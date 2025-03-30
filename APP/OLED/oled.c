#include "oled.h"
#include "font.h"
#include "string.h"
#include "stdlib.h"
//显示屏驱动.c文件

u8 OLED_GRAM[128][8]; //虚拟OLED显存

//刷新显存
void OLED_RefreshGRAM(void)
{
	u8 x,y;
	for(y=0;y<8;y++)
	{
		OLED_WR_CMD(0xb0+y);
		OLED_WR_CMD(0x01);
		OLED_WR_CMD(0x10);
		for(x=0;x<128;x++)
		 OLED_WR_DATA(OLED_GRAM[x][y]);
	}
}

//写命令
void OLED_WR_CMD(u8 cmd)
{
	u8 t;
	//OLED_CS=0;
	OLED_DC=0;//写命令
	for(t=0;t<8;t++)
  {
    if(cmd&0x80) OLED_SDA=1;
    else OLED_SDA=0;
    OLED_SCL=1;
	  OLED_SCL=0;
	  cmd<<=1;    
  }	
	//OLED_CS=1;
}
//写数据
void OLED_WR_DATA(u8 data)
{
	u8 t;
	//OLED_CS=0;
	OLED_DC=1;//写数据
	for(t=0;t<8;t++)
  {
    if(data&0x80) OLED_SDA=1;
    else OLED_SDA=0;
    OLED_SCL=1;
	  OLED_SCL=0;
	  data<<=1;    
  }	
	//OLED_CS=1;
}

//设置光标位置
void OLED_SetPos(u8 x,u8 y)
{
  OLED_WR_CMD(0xb0+y);
  OLED_WR_CMD(((x&0xf0)>>4)|0x10);
  OLED_WR_CMD((x&0x0f)|0x01);
}
//OLED画点函数
//x:0~128
//y:0~64
//mode:0不显示,1显示
void OLED_DrawPoint(u8 x,u8 y,u8 mode)
{
	if(mode) OLED_GRAM[x][y/8]|=1<<(y%8);//显示
	else OLED_GRAM[x][y/8]&=~(1<<(y%8));//不显示
}
//OLED读点函数
//x:0~128
//y:0~64
//返回:0不显示,1显示
u8 OLED_ReadPoint(u8 x,u8 y)
{
	u8 mode=(OLED_GRAM[x][y/8]&(1<<(y%8)))==(1<<(y%8))?1:0;
	return mode;
}
//清屏
void OLED_Clear(u8 clear)
{
  u8 x,y;
	for(y=0;y<8;y++)
	{
		OLED_WR_CMD(0xb0+y);
		OLED_WR_CMD(0x01);
		OLED_WR_CMD(0x10);
		for(x=0;x<128;x++)
		{
			OLED_WR_DATA(clear);
			OLED_GRAM[x][y]=clear;
		}
	}
}
//初始化OLED
void OLED_Init(void)        
{
	gpio_init(PTC,16,1,PULL_NULL);
	gpio_init(PTC,17,1,PULL_NULL);
	gpio_init(PTC,18,1,PULL_NULL);
	gpio_init(PTC,19,1,PULL_NULL);
	
  OLED_RST=0; //产生复位信号
  delay_ms(10);
	OLED_RST=1;
	OLED_WR_CMD(0xae);
  OLED_WR_CMD(0x00);
  OLED_WR_CMD(0x10);
  OLED_WR_CMD(0x40);
  OLED_WR_CMD(0x81);
  OLED_WR_CMD(0xcf); 
  OLED_WR_CMD(0xa1);
  OLED_WR_CMD(0xc8);
  OLED_WR_CMD(0xa6);
  OLED_WR_CMD(0xa8);
  OLED_WR_CMD(0x3f);
  OLED_WR_CMD(0xd3);
  OLED_WR_CMD(0x00);
  OLED_WR_CMD(0xd5);
  OLED_WR_CMD(0x80);
  OLED_WR_CMD(0xd9);
  OLED_WR_CMD(0xf1);
  OLED_WR_CMD(0xda);
  OLED_WR_CMD(0x12);
  OLED_WR_CMD(0xdb);
  OLED_WR_CMD(0x40);
  OLED_WR_CMD(0x20);
  OLED_WR_CMD(0x02);
  OLED_WR_CMD(0x8d);
  OLED_WR_CMD(0x14);
  OLED_WR_CMD(0xa4);
  OLED_WR_CMD(0xa6);
  OLED_WR_CMD(0xaf);
  OLED_Clear(255);
}
//汉字索引表
const unsigned char Hanzi_Index[]="迷你四轴飞行器参数调节遥控设置";

//在指定位置显示一个字符
void OLED_ShowChar(u8 x,u8 y,u8 num,u8 size)
{  							  
  u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);   
	num=num-' ';//得到偏移后的值
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	  
		else if(size==16)temp=asc2_1608[num][t];							
		for(t1=0;t1<8;t1++)
		{			    
		  if(temp&0x80) OLED_DrawPoint(x,y,1);
			else OLED_DrawPoint(x,y,0);
			temp<<=1;
			y++;
			if(y>=OLED_Height)return;		//超区域了
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=OLED_Width)return;	//超区域了
				break;
			}
		}  	 
	}  	
}
//m^n函数
u32 OLED_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	
//显示数字,高位为0显示
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{  
	u8 t,temp;
	u8 enshow=0;	
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
			  OLED_ShowChar(x+(size/2)*t,y,' ',size);  
 				continue;
			}else enshow=1; 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size); 
	}
}
//显示数字,高位为0显示
void OLED_ShowxNum(u8 x,u8 y,u32 num,u8 len,u8 size)
{  
	u8 t,temp;
	u8 enshow=0;	
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
			  OLED_ShowChar(x+(size/2)*t,y,'0',size);  
 				continue;
			}else enshow=1; 
		}
	 	OLED_ShowChar(x+(size/2)*t,y,temp+'0',size); 
	}
}
//显示一个指定大小的汉字
void OLED_ShowFont(u8 x,u8 y,u8 *fontL,u8 *fontH,u8 size)
{
	u8 temp,t,t1,offset=0;
	u16 y0=y;
	u8 dzk[72];   
	u8 csize=(size/8+((size%8)?1:0))*(size);//得到字体一个字符对应点阵集所占的字节数	 
	for(offset=0;offset<sizeof(Hanzi_Index);offset++)
  {
    if(*fontL==Hanzi_Index[offset]&&*fontH==Hanzi_Index[offset+1])
    {
			offset/=2;
			break;
		}
  }	
	switch(size)
	{
		case 12:
			for(t=0;t<csize;t++) dzk[t]=hz_1206[offset][t];
			break;
		case 16:
			for(t=0;t<csize;t++) dzk[t]=hz_1608[offset][t];
			break;
	} 
	for(t=0;t<csize;t++)
	{   												   
		temp=dzk[t];			//得到点阵数据                          
		for(t1=0;t1<8;t1++)
		{
			if(temp&0x80) OLED_DrawPoint(x,y,1);
			else OLED_DrawPoint(x,y,0); 
			temp<<=1;
			y++;
			if((y-y0)==size)
			{
				y=y0;
				x++;
				break;
			}
		}  	 
	}  
}
//在指定位置开始显示一个字符串	      		   
void OLED_ShowStr(u8 x,u8 y,u8 width,u8 height,u8*str,u8 size)
{					
	u16 x0=x;
	u16 y0=y;							  	  
  u8 bHz=0;     //字符或者中文  	    				    				  	  
	while(*str!=0)//数据未结束
	{ 
		if(!bHz)
		{
			if(*str>0x80)bHz=1;//中文 
			else              //字符
			{      
				if(x>(x0+width-size/2))//换行
				{				   
					y+=size;
					x=x0;	   
				}							    
				if(y>(y0+height-size))break;//越界返回      
				if(*str==13)//换行符号
				{         
					y+=size;
					x=x0;
					str++; 
				}  
				else OLED_ShowChar(x,y,*str,size);//有效部分写入 
				str++; 
				x+=size/2; //字符,为全字的一半 
			}
		}
		else//中文 
		{     
			bHz=0;//有汉字库    
		  if(x>(x0+width-size))//换行
			{	    
				y+=size;
				x=x0;		  
			}
			if(y>(y0+height-size))break;//越界返回  						     
		  OLED_ShowFont(x,y,str,str+1,size); //显示这个汉字,空心显示 
			str+=2; 
			x+=size;//下一个汉字偏移	    
		}						 
	}   
} 
//画线函数
//(x1,y1)起点坐标
//(x2,y2)终点坐标
//color线的颜色
void OLED_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u8 mode)
{
	int deltax=0,deltay=0,x=0,y=0,xinc1=0,xinc2=0,yinc1=0,yinc2=0,den=0,num=0,numadd=0,numpixels=0,curpixel=0; 
	deltax=abs(x2-x1);        
	deltay=abs(y2-y1);       
	x=x1;                       
	y=y1;                      
	if(x2>=x1)                
	{
		xinc1=1;
		xinc2=1;
	}
	else                        
	{
		xinc1=-1;
		xinc2=-1;
	}
	if(y2>=y1)                
	{
		yinc1=1;
		yinc2=1;
	}
	else                         
	{
		yinc1=-1;
		yinc2=-1;
	}
  if(deltax>=deltay)         
	{
		xinc1=0;                  
		yinc2=0;                 
		den=deltax;
		num=deltax/2;
		numadd=deltay;
		numpixels=deltax;         
	}
	else                         
	{
		xinc2=0;                  
		yinc1=0;                  
		den=deltay;
		num=deltay/2;
		numadd=deltax;
		numpixels=deltay;         
	}
  for(curpixel=0;curpixel<=numpixels;curpixel++)
  {
		OLED_DrawPoint(x,y,mode);
		num+=numadd;             
		if(num>=den)             
		{
			num-=den;               
			x+=xinc1;               
			y+=yinc1;              
		}
		x+=xinc2;               
		y+=yinc2;                
	}
}
//画矩形(空心)
void OLED_DrawRectangle(u16 x1,u16 y1,u16 x2,u16 y2,u16 mode)
{
	OLED_DrawLine(x1,y1,x2,y1,mode);
	OLED_DrawLine(x1,y1,x1,y2,mode);
	OLED_DrawLine(x1,y2,x2,y2,mode);
	OLED_DrawLine(x2,y1,x2,y2,mode);
}
//画圆算法
//(x0,y0):圆心
//r:半径
//type:0:空心 1:实心
void OLED_DrawCircle(int x0,int y0,int r,int type,u8 mode)
{
	int x=0;
	int y=r;
	int delta=2*(1-r);
	int direction;
	while(y>=0) 
	{
	  if(type==0) 
	  {
	    OLED_DrawPoint(x0+x,y0+y,mode);
	    OLED_DrawPoint(x0-x,y0+y,mode);
	    OLED_DrawPoint(x0-x,y0-y,mode);
	    OLED_DrawPoint(x0+x,y0-y,mode);
	  }
	  else 
	  {
	    OLED_DrawLine(x0+x,y0+y,x0+x,y0-y,mode);
	    OLED_DrawLine(x0-x,y0+y,x0-x,y0-y,mode);
	  }
	  if(delta<0) 
	  {
	    if((2*(delta+y)-1)<0) 
	    {
	      direction=1;
	    }
	    else 
		  {
	      direction=2;
	    }
	  }
	  else if(delta>0) 
	  {
	    if((2*(delta-x)-1)<=0) 
		  {
	      direction=2;
	    }
	    else 
	    {
	      direction=3;
	    }
	  }
	  else 
	  {
	    direction=2;
	  }
    switch(direction)
	  {
	    case 1:x++;delta+=(2*x+1);break;
	    case 2:x++;y--;delta+=2*(x-y+1);break;
	    case 3:y--;delta+=(-2*y+1);break;
	  }
  }
}
//将某一行的条目显示选中
void ShowClass(u8 x,u8 y,u8 width,u8 height,u8 press)
{
	u8 i,j;
	for(i=x;i<x+width;i++)
  {
		for(j=y;j<y+height;j++)
		{
			if(OLED_ReadPoint(i,j)==!press) OLED_DrawPoint(i,j,press);
			else OLED_DrawPoint(i,j,!press);
		}
	}
}
//显示图标和标题
void DrawBitMap(u8 *pbuf,u8 *title)
{
	u8 *p=pbuf;
	u8 i,j,k;
	for(i=34;i<93;i++)
	{
		for(j=0;j<6;j++)
		{
			for(k=j*8;k<(j+1)*8;k++)
			  OLED_DrawPoint(i,k,(*p>>(k-(j*8)))&0x01);
			p++;
		}
	}
	OLED_ShowStr((OLED_Width-strlen((char *)title)*6)/2,50,128,12,title,12);
}

