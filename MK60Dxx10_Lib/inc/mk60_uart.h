#ifndef _MK60_UART_H
#define _MK60_UART_H
#include "mk60_sys.h"
#include "stdio.h"
#include "mk60_gpio.h"
//»ðÉ½»ÒÌí¼Ó
//·ÉË¼¿¨¶ûMK60µ×²ã
//ËµÃ÷:uartµ×²ã
typedef enum
{
///////UART0//////
	UART_PA14,//UART0_TX
	UART_PA15,//UART0_RX
	UART_PB17,//UART0_TX
	UART_PB16,//UART0_RX
	UART_PD7,//UART0_TX
	UART_PD6,//UART0_RX
///////UART1//////
	UART_PE0,//UART1_TX
	UART_PE1,//UART1_RX
	UART_PC4,//UART1_TX
	UART_PC3,//UART1_RX
///////UART2//////
  UART_PD3,//UART2_TX
	UART_PD2,//UART2_RX
///////UART3//////
  UART_PE4,//UART3_TX
	UART_PE5,//UART3_RX
  UART_PB11,//UART3_TX
	UART_PB10,//UART3_RX
  UART_PC17,//UART3_TX
	UART_PC16,//UART3_RX	
///////UART4//////
  UART_PE24,//UART4_TX
	UART_PE25,//URAT4_RX
  UART_PC15,//UART4_TX
	UART_PC14,//UART4_RX
///////UART5//////
  UART_PE8,//UART5_TX
	UART_PE9,//UART5_RX	
	UART_PD9,//UART5_TX
	UART_PD8,//UART5_RX	
}UART_Pin;

//´®¿Ú¿âº¯Êý
void uart_init(UART_Type *UARTx,uint32_t bound);
void uart_sendbyte(UART_Type *UARTx,uint8_t data);

#endif
