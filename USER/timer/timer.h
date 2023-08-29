#ifndef _TIMERH
#define _TIMERH

#include "stm32f10x.h"

//PWM
#define  RCC_PwmTimer_PeriphClockCmd	RCC_APB2PeriphClockCmd
#define  RCC_PwmGPIO_PeriphClockCmd		RCC_APB2PeriphClockCmd
#define  RCC_PwmTimer_Periph_TIM		RCC_APB2Periph_TIM1
#define  RCC_PwmGPIO_Periph_GPIO		RCC_APB2Periph_GPIOA
#define  Pwm_GPIO_Pin					GPIO_Pin_8|GPIO_Pin_11
#define	 Pwm_GPIO						GPIOA
#define  Pwm_Timer						TIM1
#define  Pwm_Timer_Period				7199
#define  Pwm_Timer_Prescaler			0


//定时器
#define  RCC_Timer_PeriphClockCmd		RCC_APB1PeriphClockCmd
#define	 RCC_Timer_Periph_TIM			RCC_APB1Periph_TIM2
#define	 Timer							TIM2
#define  Timer_Period					999//10ms
#define  Timer_Prescaler				719
#define  Timer_IRQn						TIM2_IRQn


//编码器模式
#define  RCC_TimerEncorder1_PeriphClockCmd				RCC_APB1PeriphClockCmd
#define  RCC_TimerEncorder1_GPIO_PeriphClockCmd			RCC_APB2PeriphClockCmd
#define  RCC_TimerEncorder1_Periph_TIM					RCC_APB1Periph_TIM3
#define  RCC_TimerEncorder1_Periph_GPIO					RCC_APB2Periph_GPIOA
#define  TimerEncorder1									TIM3
#define  TimerEncorder1_GPIO_Pin						GPIO_Pin_6|GPIO_Pin_7
#define  TimerEncorder1_GPIO							GPIOA
#define  TimerEncorder1_Period							65535
#define  TimerEncorder1_Prescaler						0

#define  RCC_TimerEncorder2_PeriphClockCmd				RCC_APB1PeriphClockCmd
#define  RCC_TimerEncorder2_GPIO_PeriphClockCmd			RCC_APB2PeriphClockCmd
#define  RCC_TimerEncorder2_Periph_TIM					RCC_APB1Periph_TIM4
#define  RCC_TimerEncorder2_Periph_GPIO					RCC_APB2Periph_GPIOB
#define  TimerEncorder2									TIM4
#define  TimerEncorder2_GPIO_Pin						GPIO_Pin_6|GPIO_Pin_7
#define  TimerEncorder2_GPIO							GPIOB
#define  TimerEncorder2_Period							65535
#define  TimerEncorder2_Prescaler						0


void Pwm_Config(void);//定时器4配置为PWM输出
void Timer_NVIC_Config(void);
void Timer_Config(void);//定时器2配置为一般计数模式
void Timer_Init(void);//定时器初始化
void Timer_Encorder1_Config(void);//定时器3配置为编码器模式 (左边)
void Timer_Encorder2_Config(void);//定时器5配置为编码器模式 (右边)

#endif/*_TIMER_H*/
