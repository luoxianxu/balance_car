
#include "motor_control.h"

void motor_dir_config(void){
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_left_motor_dir_PeriphClockCmd(RCC_left_motor_dir_Periph_GPIO,ENABLE);
	RCC_right_motor_dir_PeriphClockCmd(RCC_right_motor_dir_Periph_GPIO,ENABLE);
	
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = left_motot_dir_GPIO_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(left_motor_dir_GPIO,&GPIO_InitStruct);
	
	GPIO_StructInit(&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = right_motot_dir_GPIO_Pin;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(right_motor_dir_GPIO,&GPIO_InitStruct);
	
	GPIO_SetBits(left_motor_dir_GPIO, GPIO_Pin_5);
	GPIO_ResetBits(left_motor_dir_GPIO, GPIO_Pin_4);//left正转
	
	GPIO_SetBits(right_motor_dir_GPIO, GPIO_Pin_0);//right正转
	GPIO_ResetBits(right_motor_dir_GPIO, GPIO_Pin_1);

}

void set_motor_dir(float *pwm){
	if(*pwm > 0){
		GPIO_SetBits(left_motor_dir_GPIO, GPIO_Pin_5);
		GPIO_ResetBits(left_motor_dir_GPIO, GPIO_Pin_4);//left正转
	
		GPIO_SetBits(right_motor_dir_GPIO, GPIO_Pin_0);//right正转
		GPIO_ResetBits(right_motor_dir_GPIO, GPIO_Pin_1);
		
		if(*pwm > 7200.0){
			*pwm = 7200.0;
		}
	}
	else if(*pwm < 0){
		GPIO_SetBits(left_motor_dir_GPIO, GPIO_Pin_4);
		GPIO_ResetBits(left_motor_dir_GPIO, GPIO_Pin_5);//left反转
	
		GPIO_SetBits(right_motor_dir_GPIO, GPIO_Pin_1);//right反转
		GPIO_ResetBits(right_motor_dir_GPIO, GPIO_Pin_0);
		if(*pwm < -7200.0){
			*pwm = -7200.0;
		}
		*pwm = -(*pwm);
	}
	if(*pwm<720)
		*pwm = 0;
}
