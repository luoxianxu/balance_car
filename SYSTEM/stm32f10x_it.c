/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include "motor_control.h"
#include <stdio.h>
#include "oled.h"
extern int16_t Target;

int16_t left_net;
int16_t rigth_net;
int16_t Mid;

float pitch,roll,yaw;
short gx,gy,gz;
uint8_t flag = 1;//获取第一个角度作为角度环的目标值
float target_angle;
uint8_t stop_flag = 0;

struct angle_pid balance_pid = {
	.kp = 420,		//150		420					//不好  420				//420
	.ki = 0.0,
	.kd = -3.00,	//-0.75		-3.55				//不好	-3.25			//-2.95
	.error = 0,
	.last_error = 0,
	.sum_error = 0,
	.k = 1
};

struct Speed_pid speed_pid = {
	.kp = 155,		//		80		170			//不好	161					//161
	.ki = 0.68,		//		0.4		0.85		//不好	0.82				//0.82
	.kd = 0.0,
	.error = 0,
	.last_error = 0,
	.sum_error = 0,
	.k = 1
};

//PD  roll
float angle_pid_calc(float angle,short gspeed,float target_angle){
	
	if(angle >= 60 || angle <= -60){	//倒下电机停止
		stop_flag = 1;
		return 0.0;
	}

	float output = 0.0;
//	printf("angle = %f\tgspeed = %d\t",angle,gspeed);
	balance_pid.error = target_angle - angle;

	if(balance_pid.error < 0.5 && balance_pid.error > -0.5)//死区设定
		balance_pid.error = 0.0;
//	printf("error = %f\t",balance_pid.error);
	
//	printf("P:%f\t	D:%f\t",balance_pid.kp*balance_pid.error,balance_pid.kd*gspeed);
	output = balance_pid.kp*balance_pid.error+balance_pid.kd*gspeed;
	balance_pid.last_error = balance_pid.error;
	output *= balance_pid.k;
//	printf("output = %4.4f\r\n",output);
	return output;
}

//PI
float speed_pid_calc(int16_t left_encorder_net,int16_t right_encorder_net,int16_t target_speed){
	if(stop_flag == 1){
		speed_pid.sum_error = 0;//清除积分
		return 0;
	}
//	float output = 0.0;
//	speed_pid.error = (left_encorder_net+right_encorder_net)-target_speed;
//	speed_pid.error = speed_pid.error*0.3 + speed_pid.last_error*0.7;			//一阶滤波
//	speed_pid.sum_error += speed_pid.error;
//	if(speed_pid.sum_error > 3000)
//		speed_pid.sum_error = 3000;
//	if(speed_pid.sum_error < -3000)
//		speed_pid.sum_error = -3000;
//	output = speed_pid.kp*speed_pid.error + speed_pid.ki*speed_pid.sum_error;
//	speed_pid.last_error = speed_pid.error;
//	return output;
	
	static float Velocity=0,Encoder_Least=0,Encoder=0;
    static float Encoder_Integral=0;

    Encoder_Least =(left_encorder_net + right_encorder_net)-target_speed;                 //===获取最新速度偏差==测量速度（左右编码器之和）-目标速度（此处为零） 
    Encoder *= 0.8;                                                  //===一阶低通滤波器       
    Encoder += Encoder_Least*0.2;                                    //===一阶低通滤波器    
    Encoder_Integral += Encoder;
    if(Encoder_Integral>1500)  
		Encoder_Integral=1500;              //===积分限幅
    if(Encoder_Integral<-1500) 
		Encoder_Integral=-1500;             //===积分限幅  
    Velocity = Encoder*speed_pid.kp+Encoder_Integral*speed_pid.ki;     //===速度控制  
    return Velocity;
	
}


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

float balance_pwm = 0.0;
float speed_pwm = 0.0;
float pwm = 0.0;
int16_t per_left_net = 0;
int16_t per_right_net = 0;

void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{	
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0){
			MPU_Get_Gyroscope(&gx,&gy,&gz);
//			printf("pitch = %f   roll = %f   yaw = %f\r\n",pitch,roll,yaw);
//			printf("gx = %d   gy = %d   gz = %d\r\n",gx,gy,gz);
			if(flag == 1){
				target_angle = 1.4374;
				OLED_Clear();
				OLED_ShowFloat(5,5,target_angle,4.4);
				OLED_Refresh();
				flag = 0;
			}
			if(stop_flag == 0){
				
				balance_pwm = angle_pid_calc(roll,gx,target_angle);//角度环计算
				
				//速度环
				int32_t left_net = TIM3->CNT;//获取左右编码器中寄存器所存放的值
				int32_t right_net = TIM4->CNT;
				left_net -= per_left_net;	 //获取两次采集的变化量
				right_net -= per_right_net;
				
				//更新比较值
				per_left_net = TIM3->CNT;
				per_right_net = TIM4->CNT;
				
				//获取编码器计数值的变化量
				if(left_net > 60000){
					left_net -= 65535;
				}
				else if(left_net < -60000){
					left_net += 65535;
				}
				
				if(right_net > 60000){
					right_net -= 65535;
				}
				else if(right_net < -60000){
					right_net += 65535;
				}
				//取反
//				right_net = -right_net;
				
				speed_pwm = speed_pid_calc(left_net,right_net,0);//速度环计算
				balance_pwm=-1500;
				pwm = balance_pwm+speed_pwm;
				set_motor_dir(&pwm);
//				printf("pwm = %f\r\n",pwm);
				
				TIM1->CCR1 = 1500;
				TIM1->CCR4 = 1500;
			}
		}
		TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
	}
	
}


void EXTI15_10_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line13) == SET){
		if(mpu_dmp_get_data(&pitch,&roll,&yaw)==0){
			MPU_Get_Gyroscope(&gx,&gy,&gz);
//			printf("pitch = %f   roll = %f   yaw = %f\r\n",pitch,roll,yaw);
//			printf("gx = %d   gy = %d   gz = %d\r\n",gx,gy,gz);
			if(flag == 1){
				target_angle = roll;
				OLED_ShowFloat(5,5,target_angle,4.4);
				OLED_Refresh();
				flag = 0;
			}
			if(stop_flag == 0){
				balance_pwm = angle_pid_calc(roll,gx,target_angle);//角度环计算
				
				//速度环
				int32_t left_net = TIM3->CNT;//获取左右编码器中寄存器所存放的值
				int32_t right_net = TIM4->CNT;
				left_net -= per_left_net;	 //获取两次采集的变化量
				right_net -= per_right_net;
				
				//更新比较值
				per_left_net = TIM3->CNT;
				per_right_net = TIM4->CNT;
				
				//获取编码器计数值的变化量
				if(left_net > 60000){
					left_net -= 65535;
				}
				else if(left_net < -60000){
					left_net += 65535;
				}
				
				if(right_net > 60000){
					right_net -= 65535;
				}
				else if(right_net < -60000){
					right_net += 65535;
				}
				
				speed_pwm = speed_pid_calc(left_net,right_net,0);//速度环计算
				printf("speed_pwm = %f\r\n",speed_pwm);
				pwm = balance_pwm+speed_pwm;
//				printf("balance_pwm = %f\tspeed_pwm = %f\r\n",balance_pwm,speed_pwm);
				set_motor_dir(&pwm);
//				printf("pwm = %f\r\n",pwm);
				
			TIM1->CCR1 = (uint16_t)pwm;
			TIM1->CCR4 = (uint16_t)pwm;
			}
		}
		EXTI_ClearITPendingBit(EXTI_Line13);
	}
}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
