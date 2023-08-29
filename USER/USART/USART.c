
#include "USART.h"
#include "stdio.h"


void USART1_Config(void)
{
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	//ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	
	//���ڽ�����������
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING; //��������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_10;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//���ڷ�����������
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	USART_InitStruct.USART_BaudRate=115200;   //���ô��ڲ�����
	USART_InitStruct.USART_StopBits=USART_StopBits_1; //һ��ֹͣλ
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStruct.USART_WordLength=USART_WordLength_8b; //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStruct.USART_Mode=USART_Mode_Tx|USART_Mode_Rx; //�շ�ģʽ
	USART_InitStruct.USART_Parity=USART_Parity_No;  //��У��λ
	USART_Init(USART1,&USART_InitStruct);
	
	USART_Cmd(USART1,ENABLE); //����ʹ��
}

void USART2_Config(void)
{
	USART_InitTypeDef USART_InitStruct;
	GPIO_InitTypeDef GPIO_InitStruct;
	//ʱ��ʹ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	//���ڽ�����������
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN_FLOATING; //��������
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	//���ڷ�����������
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_2;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
	
	
	USART_InitStruct.USART_BaudRate=115200;   //���ô��ڲ�����
	USART_InitStruct.USART_StopBits=USART_StopBits_1; //һ��ֹͣλ
	USART_InitStruct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStruct.USART_WordLength=USART_WordLength_8b; //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStruct.USART_Mode=USART_Mode_Tx|USART_Mode_Rx; //�շ�ģʽ
	USART_InitStruct.USART_Parity=USART_Parity_No;  //��У��λ
	USART_Init(USART2,&USART_InitStruct);
	
	USART_Cmd(USART2,ENABLE); //����ʹ��
}



 //����һ���ֽ�
void USART_Send(USART_TypeDef* p,uint8_t date) 
{
	USART_SendData(p,date);
	while(USART_GetFlagStatus(p,USART_FLAG_TXE) == RESET);
}
 //���������ֽ�
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
  //����һ��8λ������
void USART_SendArray(USART_TypeDef* p,uint8_t *array,uint8_t num)
{
	uint8_t i;
	for(i=0;i<num;i++)
	{
		USART_SendData(p,array[i]);
		while(USART_GetFlagStatus(p,USART_FLAG_TXE) == RESET);
	}
	
}
  //�����ַ���
void USART_SendStr(USART_TypeDef* p,uint8_t *str)
{
	do
	{
		USART_SendData(p,*(str++));
		while(USART_GetFlagStatus(p,USART_FLAG_TXE) == RESET);
	}while(*(str) != '\0');
	
} 


//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART->SR&0X40)==0);//ѭ������,ֱ���������   
    USART->DR = (u8) ch;      
	return ch;
}
#endif

//�ض���c�⺯����scanf�����ڣ��ض�����ʹ��scanf����
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
	BUFF[_cnt++]=0xAA;//֡ͷ
	BUFF[_cnt++]=0xFF;//Ŀ���ַ
	BUFF[_cnt++]=0XF1;//������
	BUFF[_cnt++]=0x05;//���ݳ���
	BUFF[_cnt++]=BYTE0(A);//��������,С��ģʽ����λ��ǰ
	BUFF[_cnt++]=BYTE1(A);//��Ҫ���ֽڽ��в�֣���������ĺ궨�弴�ɡ�
	BUFF[_cnt++]=BYTE0(B);
	BUFF[_cnt++]=BYTE1(B);
	BUFF[_cnt++]=BYTE0(C);	
//	BUFF[_cnt++]=C;
	//SC��AC��У��ֱ�ӳ�������������ļ���
	for(i=0;i<BUFF[3]+4;i++) 
	{
		sumcheck+=BUFF[i];
		addcheck+=sumcheck;
	}
	BUFF[_cnt++]=sumcheck;	
	BUFF[_cnt++]=addcheck;	
	
	for(i=0;i<_cnt;i++) USART_Send(USART,BUFF[i]);//���������������
}


