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
	gpio_init(PTE,12,1,PULL_NULL); //������
	PEout(12)=1;
	gpio_init(PTE,1,0,PULL_UP); //���뿪��
	gpio_init(PTE,3,0,PULL_UP);
	gpio_init(PTE,5,0,PULL_UP);
	gpio_init(PTE,7,0,PULL_UP);
	pit_init(PIT0,10);
  OLED_Init();
	ftm_pwm_init(FTM0,ftm_ch0,1875,440);//����ǰת	
//	ftm_pwm_init(FTM0,ftm_ch3,1875,0);//������ת
	ftm_pwm_init(FTM0,ftm_ch2,1875,440);//�ҵ��ǰת	
//	ftm_pwm_init(FTM0,ftm_ch1,1875,0);//�ҵ����ת
	ftm_pwm_init(FTM2,ftm_ch0,11719,1840); //���,200Hz	
	while(OV7725_Init());
	dma_gpio_counter_init(DMA_Channel1,PTA,19,DMA_RISING,PULL_NULL); //��������
	dma_gpio_counter_init(DMA_Channel2,PTB,21,DMA_RISING,PULL_NULL); //�ҵ������
	SetIntPrio(2,PORTB_IRQn,0); //����ͷ�ж����ȼ����
	SetIntPrio(2,PIT0_IRQn,1);//��ʱ�����ȼ���֮
  EnableInterrupts(); 	//��ȫ�����ж�
	while(1)
  {
	  Image_Decompression(Image_zip,Image_Data[0]);
	  get_mid();
		shizi_handle();
		ServoPD();
		if(PEin(7)==0) Display_Image_On_PC();  //���뿪�ص�1λ 
  }		
}
//��ʱ��0�жϺ���
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
//Ӳ�������ж�
void HardFault_Handler(void)
{
	printf("\r\nӲ������!!!");
}
