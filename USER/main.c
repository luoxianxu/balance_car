
#include "stm32f10x.h"
#include "USART.h"
#include "timer.h"
#include "mpu6050.h"
#include "delay.h"
#include "inv_mpu.h"
#include "exit_interrupt.h"
#include "oled.h"
#include "motor_control.h"

int main(void)
{
	delay_init();
	OLED_Init();
	USART2_Config();
	MPU_Init();
	while(mpu_dmp_init()){
		printf("mpu6050 dmp init failed\r\n");
		delay_ms(500);
	}
	OLED_Clear();
	
	OLED_ShowString(5,5,"OK");
	OLED_Refresh();
	delay_ms(1000);
	exit_interrupt_init();
	motor_dir_config();
	Pwm_Config();
	Timer_Encorder1_Config();
	Timer_Encorder2_Config();
//	Timer_Init();
	while(1)
	{
		
	}
	
} 
