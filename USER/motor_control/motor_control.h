
#ifndef _MOTOR_CONTROL_H
#define _MOTOR_CONTROL_H

#include "stm32f10x.h"

#define RCC_left_motor_dir_PeriphClockCmd	RCC_APB2PeriphClockCmd
#define RCC_left_motor_dir_Periph_GPIO		RCC_APB2Periph_GPIOB
#define right_motor_dir_GPIO				GPIOB
#define right_motot_dir_GPIO_Pin			GPIO_Pin_0|GPIO_Pin_1

#define RCC_right_motor_dir_PeriphClockCmd	RCC_APB2PeriphClockCmd
#define RCC_right_motor_dir_Periph_GPIO		RCC_APB2Periph_GPIOA
#define left_motor_dir_GPIO					GPIOA
#define left_motot_dir_GPIO_Pin				GPIO_Pin_4|GPIO_Pin_5

void motor_dir_config(void);
void set_motor_dir(float *pwm);

#endif/*_MOTOR_CONTROL_H*/

