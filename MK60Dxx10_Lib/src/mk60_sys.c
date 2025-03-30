#include "mk60_sys.h"
//火山灰添加
//飞思卡尔MK60底层
//说明:系统时钟初始化底层

//配置K60时钟
//内核/系统时钟为:150/1=150MHz
//Bus时钟为:150/1=150MHz
//FlexBus时钟为150/15=10MHz
//Flash时钟为:150/10=15MHz
void SystemInit(void)
{
	 WDOG->UNLOCK=0xC520;//关闭看门狗
	 WDOG->UNLOCK=0xD928;  
	 WDOG->STCTRLH&=~0x0001;
	 //模式切换:FEI->FBE->PBE->PEE
	 MCG->C1&=0X03;
	 MCG->C1|=0XB8;
	 MCG->C2&=0XCD;
	 MCG->C2|=0X10;
	 while(MCG->S&0X10);
	 while((MCG->S&0X0C)>>2!=0X02);
	 SIM->CLKDIV1=(SIM_CLKDIV1_OUTDIV1(PllClock/SystemClock-1)|SIM_CLKDIV1_OUTDIV2(PllClock/BusClock-1)|SIM_CLKDIV1_OUTDIV3(PllClock/FlexClock-1)|SIM_CLKDIV1_OUTDIV4(PllClock/FlashClock-1));
	 MCG->C5&=0XE0; //清除分频位
	 MCG->C5|=((ExternalClock/5)-1)<<0; //ExternalClock/(ExternalClock/5)=5MHz
	 MCG->C6&=0XD0; //清除倍频位
	 MCG->C6|=1<<6;
	 MCG->C6|=(PllClock/5-24)<<0; //倍频系数
	 while((MCG->S&0X20)!=0X20);
	 while((MCG->S&0X40)!=0X40);
	 MCG->C1&=0X31;
	 MCG->C1|=0X00;
	 while((MCG->S&0X0C)>>2!=0X03);
}
//开启全局中断
void EnableInterrupts(void)
{
	__enable_irq();
}
//关闭全局中断
void DisableInterrupts(void)
{
	__disable_irq();
}
//设置中断优先级
//PrioGroup:Group0~Group7
//IRQn:中断向量
//prio:设置优先级,越小优先级越大
void SetIntPrio(uint32_t PrioGroup,IRQn_Type IRQn,uint32_t prio)
{
	NVIC_SetPriorityGrouping(PrioGroup);
  NVIC_SetPriority(IRQn,prio);	
}
//微秒级
void delay_us(uint16_t nus)
{
	uint32_t temp;
	SysTick->CTRL|=0x04;//设置系统滴答定时器的时钟为内核时钟
  SysTick->LOAD=nus*SystemClock;//时间加载
  SysTick->VAL=0x00;//清空计数器
  SysTick->CTRL|=0x01;//开始倒数   
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0x01&&!(temp&(1<<16)));//等待时间到达   
	SysTick->CTRL&=~0x01;//关闭计数器
}
//毫秒级
void delay_ms(uint16_t nms)
{
	uint16_t t;
	for(t=0;t<nms;t++)
	{
		delay_us(1000);
	}
}

