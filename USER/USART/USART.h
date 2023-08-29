#ifndef _USART_H
#define _USART_H

#include "stm32f10x.h"

#define USART     				USART2

/**********Ϊ������������λ����Э�鶨��ı���****************************/
//cupΪС��ģʽ�洢��Ҳ�����ڴ洢��ʱ�򣬵�λ������0�ֽڣ���λ��1�ֽ�
#define BYTE0(dwTemp)       (*(char *)(&dwTemp))	 //ȡ��int�ͱ����ĵ��ֽ�
#define BYTE1(dwTemp)       (*((char *)(&dwTemp) + 1))	 //	ȡ�洢�ڴ˱�����һ�ڴ��ֽڵ����ݣ����ֽ�
#define BYTE2(dwTemp)       (*((char *)(&dwTemp) + 2))
#define BYTE3(dwTemp)       (*((char *)(&dwTemp) + 3))

void USART1_Config(void);
void USART2_Config(void);

void USART_Send(USART_TypeDef* p,uint8_t date);//����һ���ֽ�
void USART_SendHalfword(USART_TypeDef* p,uint16_t date);//���������ֽ�
void USART_SendArray(USART_TypeDef* p,uint8_t *array,uint8_t num);//����һ��8λ������
void USART_SendStr(USART_TypeDef* p,uint8_t *str);//����һ���ַ���

void sent_data(int16_t A,int16_t B,float C);
#endif

