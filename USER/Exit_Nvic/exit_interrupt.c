
#include "exit_interrupt.h"

void exit_interrupt_nvic_config(void){
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef ExitInterruptNVIC_InitStruct;
	ExitInterruptNVIC_InitStruct.NVIC_IRQChannel = exit_interrupt_IRQn;
	ExitInterruptNVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 0;
	ExitInterruptNVIC_InitStruct.NVIC_IRQChannelSubPriority = 0;
	ExitInterruptNVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&ExitInterruptNVIC_InitStruct);
}

void exit_interrupt_config(void){
	RCC_Exit_Initerrupt_PeriphClockCmd(RCC_Exit_Initerrupt_Periph_GPIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);			//使用外部中断必须使用复用
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = exit_interrupt_GPIO_Pin;
	GPIO_Init(exit_interrupt_GPIO,&GPIO_InitStruct);
	
	GPIO_EXTILineConfig(exit_interrupt_GPIO_PortSource,exit_interrupt_GPIO_PinSource);
	
	EXTI_InitTypeDef Exti_InitStruct;
	Exti_InitStruct.EXTI_Line = exit_interrupt_EXTI_Line;
	Exti_InitStruct.EXTI_LineCmd = ENABLE;
	Exti_InitStruct.EXTI_Mode = exit_interrupt_EXTI_Mode;
	Exti_InitStruct.EXTI_Trigger = exit_interrupt_EXTI_Trigger;
	EXTI_Init(&Exti_InitStruct);
}

void exit_interrupt_init(void){
	exit_interrupt_nvic_config();
	exit_interrupt_config();
}
