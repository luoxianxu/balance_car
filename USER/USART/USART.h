#ifndef _USART_H
#define _USART_H

#include "stm32f10x.h"

#define USART     				USART2

/**********为了匿名四轴上位机的协议定义的变量****************************/
//cup为小端模式存储，也就是在存储的时候，低位被存在0字节，高位在1字节
#define BYTE0(dwTemp)       (*(char *)(&dwTemp))	 //取出int型变量的低字节
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))	 //	取存储在此变量下一内存字节的内容，高字节
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

void USART1_Config(void);
void USART2_Config(void);

void USART_Send(USART_TypeDef* p,uint8_t date);//发送一个字节
void USART_SendHalfword(USART_TypeDef* p,uint16_t date);//发送两个字节
void USART_SendArray(USART_TypeDef* p,uint8_t *array,uint8_t num);//发送一个8位的数组
void USART_SendStr(USART_TypeDef* p,uint8_t *str);//发送一个字符串

void sent_data(int16_t A,int16_t B,float C);
#endif

