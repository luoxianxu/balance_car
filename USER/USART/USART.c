
#include "USART.h"
#include "stdio.h"


void USART1_Config(void)
{
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	//时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	
	//串口接受引脚配置
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//串口发送引脚配置
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	USART_InitStruct.USART_BaudRate=115200;   //配置串口波特率
	USART_InitStruct.USART_StopBits=USART_StopBits_1; //一个停止位
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStruct.USART_WordLength=USART_WordLength_8b; //字长为8位数据格式
	USART_InitStruct.USART_Mode=USART_Mode_Tx|USART_Mode_Rx; //收发模式
	USART_InitStruct.USART_Parity=USART_Parity_No;  //无校验位
	USART_Init(USART1,&USART_InitStruct);
	
	USART_Cmd(USART1,ENABLE); //串口使能
}

void USART2_Config(void)
{
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	//时钟使能
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//串口接受引脚配置
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//串口发送引脚配置
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;  //复用推挽输出
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	USART_InitStruct.USART_BaudRate=115200;   //配置串口波特率
	USART_InitStruct.USART_StopBits=USART_StopBits_1; //一个停止位
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStruct.USART_WordLength=USART_WordLength_8b; //字长为8位数据格式
	USART_InitStruct.USART_Mode=USART_Mode_Tx|USART_Mode_Rx; //收发模式
	USART_InitStruct.USART_Parity=USART_Parity_No;  //无校验位
	USART_Init(USART2,&USART_InitStruct);
	
	USART_Cmd(USART2,ENABLE); //串口使能
}



 //发送一个字节
void USART_Send(USART_TypeDef* p,uint8_t date) 
{
	USART_SendData(p,date);
	while(USART_GetFlagStatus(p,USART_FLAG_TXE) == RESET);
}
 //发送两个字节
void USART_SendHalfword(USART_TypeDef* p,uint16_t date)
{
	uint8_t temp_H,temp_L;
	temp_H=(date &0xff00)>>8;
	temp_L=date&0xff;
	USART_SendData(p,temp_H);
	while(USART_GetFlagStatus(p,USART_FLAG_TXE) == RESET);
	USART_SendData(p,temp_L);
	while(USART_GetFlagStatus(p,USART_FLAG_TXE) == RESET);
}
  //发送一个8位的数组
void USART_SendArray(USART_TypeDef* p,uint8_t *array,uint8_t num)
{
	uint8_t i;
	for(i=0;i<num;i++)
	{
		USART_SendData(p,array[i]);
		while(USART_GetFlagStatus(p,USART_FLAG_TXE) == RESET);
	}
	
}
  //发送字符串
void USART_SendStr(USART_TypeDef* p,uint8_t *str)
{
	do
	{
		USART_SendData(p,*(str++));
		while(USART_GetFlagStatus(p,USART_FLAG_TXE) == RESET);
	}while(*(str) != '\0');
	
} 


//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART->SR&0X40)==0);//循环发送,直到发送完毕   
    USART->DR = (u8) ch;      
	return ch;
}
#endif

//重定向c库函数到scanf到串口，重定向后可使用scanf函数
int fgetc(FILE *f)
{
	while(USART_GetFlagStatus(USART,USART_FLAG_RXNE)==RESET);
	return (int)USART_ReceiveData(USART);
}


u8 BUFF[30];

void sent_data(int16_t A,int16_t B,float C)
{
	int i;
	u8 sumcheck = 0;
	u8 addcheck = 0;
	u8 _cnt=0;
	BUFF[_cnt++]=0xAA;//帧头
	BUFF[_cnt++]=0xFF;//目标地址
	BUFF[_cnt++]=0XF1;//功能码
	BUFF[_cnt++]=0x05;//数据长度
	BUFF[_cnt++]=BYTE0(A);//数据内容,小段模式，低位在前
	BUFF[_cnt++]=BYTE1(A);//需要将字节进行拆分，调用上面的宏定义即可。
	BUFF[_cnt++]=BYTE0(B);
	BUFF[_cnt++]=BYTE1(B);
	BUFF[_cnt++]=BYTE0(C);	
//	BUFF[_cnt++]=C;
	//SC和AC的校验直接抄最上面上面简介的即可
	for(i=0;i<BUFF[3]+4;i++) 
	{
		sumcheck+=BUFF[i];
		addcheck+=sumcheck;
	}
	BUFF[_cnt++]=sumcheck;	
	BUFF[_cnt++]=addcheck;	
	
	for(i=0;i<_cnt;i++) USART_Send(USART,BUFF[i]);//串口逐个发送数据
}


