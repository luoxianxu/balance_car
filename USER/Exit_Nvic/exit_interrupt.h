
#ifndef _EXIT_INTERRUPT_H
#define _EXIT_INTERRUPT_H

#include "stm32f10x.h"

#define RCC_Exit_Initerrupt_PeriphClockCmd		RCC_APB2PeriphClockCmd
#define RCC_Exit_Initerrupt_Periph_GPIO			RCC_APB2Periph_GPIOB
#define exit_interrupt_GPIO						GPIOB
#define exit_interrupt_GPIO_Pin					GPIO_Pin_13

#define exit_interrupt_IRQn						EXTI15_10_IRQn
#define exit_interrupt_GPIO_PortSource			GPIO_PortSourceGPIOB
#define exit_interrupt_GPIO_PinSource			GPIO_PinSource13

#define exit_interrupt_EXTI_Line				EXTI_Line13
#define exit_interrupt_EXTI_Mode				EXTI_Mode_Interrupt
#define exit_interrupt_EXTI_Trigger				EXTI_Trigger_Falling

void exit_interrupt_nvic_config(void);
void exit_interrupt_config(void);
void exit_interrupt_init(void);


#endif /*_EXIT_INTERRUPT_H*/
