#ifndef _HARDWARE_OLED_H
#define _HARDWARE_OLED_H 
#include "stm32f10x.h"
//#include <stdlib.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define OLED_SCL GPIO_PORT_P6,GPIO_PIN7    //���Ĵ˴��Ը�����Ļ����MSP432�Ľӿ�
//#define OLED_SDA GPIO_PORT_P6,GPIO_PIN6
//#define OLED_RES GPIO_PORT_P3,GPIO_PIN5
//#define OLED_DC  GPIO_PORT_P4,GPIO_PIN4
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//D0
#define OLED_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_9)           //SCK
#define OLED_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_9)
//DI
#define OLED_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_8)           //MOSI
#define OLED_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_8)
//RES
#define OLED_RST_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_15)           //RST
#define OLED_RST_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_15)
//DC
#define OLED_DC_Clr()   GPIO_ResetBits(GPIOB,GPIO_Pin_14)            //DC
#define OLED_DC_Set()   GPIO_SetBits(GPIOB,GPIO_Pin_14)

#define OLED_CMD  0	                                                           //д����
#define OLED_DATA 1	//д����

#define u8 unsigned char
#define u32 unsigned int
void OLED_DisplayTurn(void);                                                   //��Ļ��ʾ��ת
void OLED_Refresh(void);                                                       //�����Դ浽OLED	
void OLED_Clear(void);                                                         //��������
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);                                   //����(�ߵ������˵�x1,y1,x2,y2)
void OLED_ShowString(u8 x,u8 y,u8 *chr);                                       //��ʾ�ַ���(�ַ�������x��y,�ַ���)
void OLED_ShowInt(u8 x,u8 y,long int num,u8 len);                              //��ʾ����(��ʾλ��x��y,��Ҫ��ʾ����ֵ,��ʾλ��<��λС����λ��ʾ������λ��0����>)
void OLED_ShowFloat(u8 x,u8 y,double num,double len);                          //��ʾ������(��ʾλ��x��y,��Ҫ��ʾ��ֵ����ʾλ��m.n<n<=8>:����λ��,n:С��λ��>)
void OLED_ShowChineseStr(u8 x,u8 y,u8* str);                                   //��ʾ�����ַ���
void OLED_Init(void);                                                          //OLED�ĳ�ʼ��
void OLED_DrowFrame(u8 x1,u8 y1,u8 x2,u8 y2);       //�����η���((x1,y1->x2,y2)Ϊ�Խ���)

#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//��Ļ��������:128*64
//�ַ�ȡģ��ʽ;����ʽ,����ȡģ��ʽ:����ʽ
//��OLED_ShowFloat()�����У����Զ�Ϊnum+0.000 000 001
//��ʾ�����ַ�������ʾ���������������Զ�����
//���޸�����Ļ��ʾ���ݺ�Ҫ�����Դ浽OLED	
