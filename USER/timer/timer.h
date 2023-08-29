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


//��ʱ��
#define  RCC_Timer_PeriphClockCmd		RCC_APB1PeriphClockCmd
#define	 RCC_Timer_Periph_TIM			RCC_APB1Periph_TIM2
#define	 Timer							TIM2
#define  Timer_Period					999//10ms
#define  Timer_Prescaler				719
#define  Timer_IRQn						TIM2_IRQn


//������ģʽ
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


void Pwm_Config(void);//��ʱ��4����ΪPWM���
void Timer_NVIC_Config(void);
void Timer_Config(void);//��ʱ��2����Ϊһ�����ģʽ
void Timer_Init(void);//��ʱ����ʼ��
void Timer_Encorder1_Config(void);//��ʱ��3����Ϊ������ģʽ (���)
void Timer_Encorder2_Config(void);//��ʱ��5����Ϊ������ģʽ (�ұ�)

#endif/*_TIMER_H*/
