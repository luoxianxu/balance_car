#ifndef _HARDWARE_OLED_H
#define _HARDWARE_OLED_H 
#include "stm32f10x.h"
//#include <stdlib.h>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//#define OLED_SCL GPIO_PORT_P6,GPIO_PIN7    //更改此处以更改屏幕接入MSP432的接口
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

#define OLED_CMD  0	                                                           //写命令
#define OLED_DATA 1	//写数据

#define u8 unsigned char
#define u32 unsigned int
void OLED_DisplayTurn(void);                                                   //屏幕显示翻转
void OLED_Refresh(void);                                                       //更新显存到OLED	
void OLED_Clear(void);                                                         //清屏函数
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2);                                   //画线(线的两个端点x1,y1,x2,y2)
void OLED_ShowString(u8 x,u8 y,u8 *chr);                                       //显示字符串(字符串行列x、y,字符串)
void OLED_ShowInt(u8 x,u8 y,long int num,u8 len);                              //显示整数(显示位置x、y,需要显示的数值,显示位数<从位小到大位显示，多余位用0补齐>)
void OLED_ShowFloat(u8 x,u8 y,double num,double len);                          //显示浮点数(显示位置x、y,需要显示的值，显示位数m.n<n<=8>:整数位数,n:小数位数>)
void OLED_ShowChineseStr(u8 x,u8 y,u8* str);                                   //显示中文字符串
void OLED_Init(void);                                                          //OLED的初始化
void OLED_DrowFrame(u8 x1,u8 y1,u8 x2,u8 y2);       //画矩形方框((x1,y1->x2,y2)为对角线)

#endif
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//屏幕像素数量:128*64
//字符取模方式;逐列式,汉字取模方式:列行式
//在OLED_ShowFloat()函数中，会自动为num+0.000 000 001
//显示中文字符串和显示浮点数函数不会自动换行
//在修改完屏幕显示内容后都要更新显存到OLED	
