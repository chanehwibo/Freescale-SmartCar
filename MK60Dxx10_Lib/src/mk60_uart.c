#include "mk60_uart.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:uart底层

//uart初始化
//UARTx:UART1,UART2...
//bound:波特率
void uart_init(UART_Type *UARTx,uint32_t bound)
{
	switch((uint32_t)UARTx)
	{
		case UART0_BASE:
		{
			SIM->SCGC4|=1<<10;
			if(UART_TX==UART_PA14)
			{
				SIM->SCGC5|=1<<9;
				gpio_alf_init(PTA,14,ALF3);
			}
			else if(UART_TX==UART_PB17)
			{
				SIM->SCGC5|=1<<10;
				gpio_alf_init(PTB,17,ALF3);
			}
      else if(UART_TX==UART_PD7)
			{
				SIM->SCGC5|=1<<12;
				gpio_alf_init(PTD,7,ALF3);
			}				
			if(UART_RX==UART_PA15)
			{
				SIM->SCGC5|=1<<9;
				gpio_alf_init(PTA,15,ALF3);
			}
			else if(UART_RX==UART_PB16)
			{
				SIM->SCGC5|=1<<10;
				gpio_alf_init(PTB,16,ALF3);
			}
			else if(UART_RX==UART_PD6)
			{
				SIM->SCGC5|=1<<12;
				gpio_alf_init(PTD,6,ALF3);
			}
			if(USE_RX) NVIC_EnableIRQ(UART0_RX_TX_IRQn);
			break;
		}
		case UART1_BASE:
		{
			SIM->SCGC4|=1<<11;
			if(UART_TX==UART_PE0)
			{
				SIM->SCGC5|=1<<13;
				gpio_alf_init(PTE,0,ALF3);
			}
			else if(UART_TX==UART_PC4)
			{
				SIM->SCGC5|=1<<11;
				gpio_alf_init(PTC,4,ALF3);
			}
			if(UART_RX==UART_PE1)
			{
				SIM->SCGC5|=1<<13;
				gpio_alf_init(PTE,1,ALF3);
			}
			else if(UART_RX==UART_PC3)
			{
				SIM->SCGC5|=1<<11;
				gpio_alf_init(PTC,3,ALF3);
			}
			if(USE_RX) NVIC_EnableIRQ(UART1_RX_TX_IRQn);
			break;
		}
		case UART2_BASE:
		{
			SIM->SCGC4|=1<<12;
			if(UART_TX==UART_PD3)
			{
				SIM->SCGC5|=1<<12;
				gpio_alf_init(PTD,3,ALF3);
			}
			if(UART_RX==UART_PD2)
			{
				SIM->SCGC5|=1<<12;
				gpio_alf_init(PTD,2,ALF3);
			}
			if(USE_RX) NVIC_EnableIRQ(UART2_RX_TX_IRQn);
			break;
		}
		case UART3_BASE:
		{
			SIM->SCGC4|=1<<13;
			if(UART_TX==UART_PE4)
			{
				SIM->SCGC5|=1<<12;
				gpio_alf_init(PTE,4,ALF3);
			}
			else if(UART_TX==UART_PB11)
			{
				SIM->SCGC5|=1<<10;
				gpio_alf_init(PTB,11,ALF3);
			}
			else if(UART_TX==UART_PC17)
			{
				SIM->SCGC5|=1<<11;
				gpio_alf_init(PTC,17,ALF3);
			}
			if(UART_RX==UART_PE5)
			{
				SIM->SCGC5|=1<<13;
				gpio_alf_init(PTE,5,ALF3);
			}
			else if(UART_RX==UART_PB10)
			{
				SIM->SCGC5|=1<<10;
				gpio_alf_init(PTB,10,ALF3);
			}
			else if(UART_RX==UART_PC16)
			{
				SIM->SCGC5|=1<<11;
				gpio_alf_init(PTC,16,ALF3);
			}
			if(USE_RX) NVIC_EnableIRQ(UART3_RX_TX_IRQn);
			break;
		}
		case UART4_BASE:
		{
			SIM->SCGC1|=1<<10;
			if(UART_TX==UART_PE24)
			{
				SIM->SCGC5|=1<<13;
				gpio_alf_init(PTE,24,ALF3);
			}
			else if(UART_TX==UART_PC15)
			{
				SIM->SCGC5|=1<<11;
				gpio_alf_init(PTC,15,ALF3);
			}
			if(UART_RX==UART_PE25)
			{
				SIM->SCGC5|=1<<13;
				gpio_alf_init(PTE,25,ALF3);
			}
			else if(UART_RX==UART_PC14)
			{
				SIM->SCGC5|=1<<11;
				gpio_alf_init(PTC,14,ALF3);
			}
			if(USE_RX) NVIC_EnableIRQ(UART4_RX_TX_IRQn);
			break;
		}
		case UART5_BASE:
		{
			SIM->SCGC1|=1<<11;
			if(UART_TX==UART_PE8)
			{
				SIM->SCGC5|=1<<13;
				gpio_alf_init(PTE,8,ALF3);
			}
			else if(UART_TX==UART_PD9)
			{
				SIM->SCGC5|=1<<12;
				gpio_alf_init(PTD,9,ALF3);
			}
			if(UART_RX==UART_PE9)
			{
				SIM->SCGC5|=1<<13;
				gpio_alf_init(PTE,9,ALF3);
			}
			else if(UART_RX==UART_PD8)
			{
				SIM->SCGC5|=1<<12;
				gpio_alf_init(PTD,8,ALF3);
			}
			if(USE_RX) NVIC_EnableIRQ(UART5_RX_TX_IRQn);
			break;
		}
		default:break;
	}
	UARTx->C2=0X00;//关闭发送和接收
	UARTx->C1=0X00;//数据位为8位
	UARTx->BDH|=(uint8_t)(SystemClock*1000000/(16*bound))>>8;
	UARTx->BDL|=(uint8_t)(SystemClock*1000000/(16*bound));
  UARTx->C2|=1<<3;//开启发送
	if(USE_RX) UARTx->C2|=1<<2;//开启接收
}
//发送一个字节数据
void uart_sendbyte(UART_Type *UARTx,uint8_t data)
{
	while((UARTx->S1&0X80)!=0X80);
	UARTx->D=data;
}
#if 1
#pragma import(__use_no_semihosting)                             
struct __FILE 
{ 
	int handle; 
}; 
FILE __stdout;        
_sys_exit(int x) 
{ 
	x=x; 
} 
//重定向fputc函数
int fputc(int ch,FILE *f)
{      
	uart_sendbyte(UART_Printf,ch);     
	return ch;
}
#endif


