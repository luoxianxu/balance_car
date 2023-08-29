#include "timer.h"

void Pwm_Config(void)      //定时器4配置为PWM波配置
{
	TIM_TimeBaseInitTypeDef Time_InitStruct;
	TIM_OCInitTypeDef TIM_OCInitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	//时钟使能
	RCC_PwmTimer_PeriphClockCmd(RCC_PwmTimer_Periph_TIM,ENABLE);
	RCC_PwmGPIO_PeriphClockCmd(RCC_PwmGPIO_Periph_GPIO,ENABLE);
	//初始化GPIO口
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin=Pwm_GPIO_Pin;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(Pwm_GPIO,&GPIO_InitStruct);
	//定时器配置
	Time_InitStruct.TIM_Prescaler=Pwm_Timer_Prescaler;
	Time_InitStruct.TIM_Period=Pwm_Timer_Period;
	Time_InitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	Time_InitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	Time_InitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit(Pwm_Timer,&Time_InitStruct);
	//PWM波配置
	TIM_OCInitStruct.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStruct.TIM_Pulse=0;
	TIM_OCInitStruct.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;
	
	TIM_OC1PreloadConfig(Pwm_Timer,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(Pwm_Timer,TIM_OCPreload_Enable);
	
	TIM_OC1Init(Pwm_Timer,&TIM_OCInitStruct);
	TIM_OC4Init(Pwm_Timer,&TIM_OCInitStruct);
	
	TIM_CtrlPWMOutputs(Pwm_Timer,ENABLE);
	TIM_Cmd(Pwm_Timer,ENABLE);
}

void Timer_NVIC_Config(void){
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitStruct.NVIC_IRQChannel=Timer_IRQn;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority=1;
	NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVIC_InitStruct);
}

void Timer_Config(void)		//定时器2配置为普通定时模式（用于定时对编码器进行读数）
{
	//定义结构体变量
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	
	//使能TIM2
	RCC_Timer_PeriphClockCmd(RCC_Timer_Periph_TIM,ENABLE);
	
	//定时器结构体配置
	TIM_InitStruct.TIM_Prescaler=Timer_Prescaler;   
	TIM_InitStruct.TIM_Period=Timer_Period;                                
	TIM_InitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(Timer,&TIM_InitStruct);
	
	TIM_ITConfig(Timer,TIM_IT_Update,ENABLE);
	TIM_Cmd(Timer,ENABLE);
}

void Timer_Init(void){
	Timer_Config();
	Timer_NVIC_Config();
}

void Timer_Encorder1_Config(void)  //左边  定时器3配置为编码器模式（只有ch1和ch2能作为编码器引脚）
{
	//定义结构体变量
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	//使能TIM3和GPIOA
	RCC_TimerEncorder1_PeriphClockCmd(RCC_TimerEncorder1_Periph_TIM,ENABLE);
	RCC_TimerEncorder1_GPIO_PeriphClockCmd(RCC_TimerEncorder1_Periph_GPIO,ENABLE);

	//GPIO口配置
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;   //浮空输入
	GPIO_InitStruct.GPIO_Pin=TimerEncorder1_GPIO_Pin;
	GPIO_Init(TimerEncorder1_GPIO,&GPIO_InitStruct);
	
	//TIM3配置
	TIM_TimeBaseStructInit(&TIM_InitStruct);
	TIM_InitStruct.TIM_Prescaler=TimerEncorder1_Prescaler;
	TIM_InitStruct.TIM_Period=TimerEncorder1_Period;
	TIM_InitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TimerEncorder1,&TIM_InitStruct);
	
	TIM_EncoderInterfaceConfig(TimerEncorder1,TIM_EncoderMode_TI12,TIM_ICPolarity_Falling,TIM_ICPolarity_Falling);
	
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_ICFilter=0;
	TIM_ICInit(TimerEncorder1,&TIM_ICInitStruct);
	
	TimerEncorder1->CNT=0;
	TIM_Cmd(TimerEncorder1,ENABLE);
}

void Timer_Encorder2_Config(void)  //右边  定时器1配置为编码器模式（只有ch1和ch2能作为编码器引脚）
{
	//定义结构体变量
	GPIO_InitTypeDef GPIO_InitStruct;
	TIM_TimeBaseInitTypeDef TIM_InitStruct;
	TIM_ICInitTypeDef TIM_ICInitStruct;
	
	//使能TIM1和GPIOA
	RCC_TimerEncorder2_PeriphClockCmd(RCC_TimerEncorder2_Periph_TIM,ENABLE);
	RCC_TimerEncorder2_GPIO_PeriphClockCmd(RCC_TimerEncorder2_Periph_GPIO,ENABLE);

	//GPIO口配置
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING;   //浮空输入
	GPIO_InitStruct.GPIO_Pin=TimerEncorder2_GPIO_Pin;
	GPIO_Init(TimerEncorder2_GPIO,&GPIO_InitStruct);
	
	//TIM1配置
	TIM_TimeBaseStructInit(&TIM_InitStruct);
	TIM_InitStruct.TIM_Prescaler=TimerEncorder2_Prescaler;
	TIM_InitStruct.TIM_Period=TimerEncorder2_Period;
	TIM_InitStruct.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_InitStruct.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TimerEncorder2,&TIM_InitStruct);
	
	TIM_EncoderInterfaceConfig(TimerEncorder2,TIM_EncoderMode_TI12,TIM_ICPolarity_Falling,TIM_ICPolarity_Falling);
	TIM_ICStructInit(&TIM_ICInitStruct);
	TIM_ICInitStruct.TIM_ICFilter=0;
	TIM_ICInit(TimerEncorder2,&TIM_ICInitStruct);
	
	TimerEncorder2->CNT=0;
	TIM_Cmd(TimerEncorder2,ENABLE);
}
