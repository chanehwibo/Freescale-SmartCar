#include "mk60_sys.h"
#include "ov7725.h"
#include "oled.h"
#include "control.h"
#include "servo_pd.h"
#include "motor_pid.h"

int main(void) 
{
	DisableInterrupts(); 
	uart_init(UART4,256000);
	gpio_init(PTD,15,1,PULL_NULL);
	gpio_init(PTE,12,1,PULL_NULL); //蜂鸣器
	PEout(12)=1;
	gpio_init(PTE,1,0,PULL_UP); //拨码开关
	gpio_init(PTE,3,0,PULL_UP);
	gpio_init(PTE,5,0,PULL_UP);
	gpio_init(PTE,7,0,PULL_UP);
	pit_init(PIT0,10);
  OLED_Init();
	ftm_pwm_init(FTM0,ftm_ch0,1875,440);//左电机前转	
//	ftm_pwm_init(FTM0,ftm_ch3,1875,0);//左电机后转
	ftm_pwm_init(FTM0,ftm_ch2,1875,440);//右电机前转	
//	ftm_pwm_init(FTM0,ftm_ch1,1875,0);//右电机后转
	ftm_pwm_init(FTM2,ftm_ch0,11719,1840); //舵机,200Hz	
	while(OV7725_Init());
	dma_gpio_counter_init(DMA_Channel1,PTA,19,DMA_RISING,PULL_NULL); //左电机测速
	dma_gpio_counter_init(DMA_Channel2,PTB,21,DMA_RISING,PULL_NULL); //右电机测速
	SetIntPrio(2,PORTB_IRQn,0); //摄像头中断优先级最高
	SetIntPrio(2,PIT0_IRQn,1);//定时器优先级次之
  EnableInterrupts(); 	//开全局总中断
	while(1)
  {
	  Image_Decompression(Image_zip,Image_Data[0]);
	  get_mid();
		shizi_handle();
		ServoPD();
		if(PEin(7)==0) Display_Image_On_PC();  //拨码开关第1位 
  }		
}
//定时器0中断函数
u16 t;
void PIT0_IRQHandler(void)
{
	clear_pit_int_flag(PIT0);
	LeftMotorPID();
	RightMotorPID();
//	OLED_ShowxNum(0,0,dma_get_counter(DMA_Channel1),3,12);
//	OLED_ShowxNum(0,24,dma_get_counter(DMA_Channel2),3,12);
//	Display_Image_On_OLED();
//	OLED_RefreshGRAM();	
	t++;
	if(t==3) {t=0;PDout(15)=~PDout(15);} 
}
//硬件错误中断
void HardFault_Handler(void)
{
	printf("\r\n硬件错误!!!");
}
