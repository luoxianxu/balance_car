#include "oled.h"
#include "oledfont.h"

u8 OLED_GRAM[144][8];
//写数据/命令函数(0命令1数据)
void OLED_WR_Byte(u8 dat,u8 cmd)
{	
	u8 i;			  
	if(cmd)
	  OLED_DC_Set();
	else
	  OLED_DC_Clr();
	for(i=0;i<8;i++)
	{
		OLED_SCLK_Clr();
		if(dat&0x80)
		   OLED_SDIN_Set();
		else 
		   OLED_SDIN_Clr();
		OLED_SCLK_Set();
		dat<<=1;   
	}
	OLED_DC_Set();   	  
}
//画点
void OLED_DrawPoint(u8 x,u8 y)
{
	u8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[x][i]|=n;
}
//清除一个点
void OLED_ClearPoint(u8 x,u8 y)
{
	u8 i,m,n;
	i=y/8;
	m=y%8;
	n=1<<m;
	OLED_GRAM[x][i]=~OLED_GRAM[x][i];
	OLED_GRAM[x][i]|=n;
	OLED_GRAM[x][i]=~OLED_GRAM[x][i];
}
//在指定位置显示一个字符,包括部分字符
void OLED_ShowChar(u8 x,u8 y,u8 chr)
{
	u8 i,m,temp,chr1;
	u8 y0=y; 
	chr1=chr-' ';   
	for(i=0;i<16;i++)
	{
    temp=asc2_1608[chr1][i];
		for(m=0;m<8;m++)          
		{
			if(temp&0x80)OLED_DrawPoint(x,y);
			else OLED_ClearPoint(x,y);
			temp<<=1;
			y++;
			if((y-y0)==16)
			{
				y=y0;
				x++;
				break;
      }
		}
  }
}
//计算m^n
u32 OLED_Pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)
	  result*=m;
	return result;
}
//显示汉字//num:汉字对应的序号
void OLED_ShowChinese(u8 x,u8 y,u8 num)
{
	u8 i,m,n=0,temp,chr1;
	u8 x0=x,y0=y;
	u8 size3=2;
	while(size3--)
	{
		chr1=num*2+n;
		n++;
		for(i=0;i<16;i++)
		{
			temp=Hzk1[chr1][i];
			for(m=0;m<8;m++)
			{
				if(temp&0x01)OLED_DrawPoint(x,y);
				else OLED_ClearPoint(x,y);
				temp>>=1;
				y++;
			}
			x++;
			if((x-x0)==16)
			{
				x=x0;
				y0=y0+8;
			}
			y=y0;
		}
	}
}
//配置写入数据的起始位置
void OLED_WR_BP(u8 x,u8 y)
{
	OLED_WR_Byte(0xb0+y,OLED_CMD);//设置行起始地址
	OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
	OLED_WR_Byte((x&0x0f),OLED_CMD);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void OLED_DisplayTurn(void)
{
			OLED_WR_Byte(0xC0,OLED_CMD);               
			OLED_WR_Byte(0xA0,OLED_CMD);
}
void OLED_Refresh(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	{
	   OLED_WR_Byte(0xb0+i,OLED_CMD); 
	   OLED_WR_Byte(0x00,OLED_CMD);    
	   OLED_WR_Byte(0x10,OLED_CMD);   
	   for(n=0;n<128;n++)
		 OLED_WR_Byte(OLED_GRAM[n][i],OLED_DATA);
  }
}
void OLED_Clear(void)
{
	u8 i,n;
	for(i=0;i<8;i++)
	   for(n=0;n<128;n++)
			 OLED_GRAM[n][i]=0; 
	OLED_Refresh(); 
}
void OLED_DrawLine(u8 x1,u8 y1,u8 x2,u8 y2)
{
	u8 i,k,k1,k2;
//	if((x1<0)||(x2>128)||(y1<0)||(y2>64)||(x1>x2)||(y1>y2))return;
	if((x2>128)||(y2>64)||(x1>x2)||(y1>y2))return;	//修改
	if(x1==x2)                                                                   
	{
			for(i=0;i<(y2-y1);i++)
			{
				OLED_DrawPoint(x1,y1+i);
			}
  }
	else if(y1==y2)                                                             
	{
			for(i=0;i<(x2-x1);i++)
			{
				OLED_DrawPoint(x1+i,y1);
			}
  }
	else                                                                        
	{
		k1=y2-y1;
		k2=x2-x1;
		k=k1*10/k2;
		for(i=0;i<(x2-x1);i++)
			{
			  OLED_DrawPoint(x1+i,y1+i*k/10);
			}
	}
	OLED_Refresh();
} 
void OLED_ShowString(u8 x,u8 y,u8 *chr)
{
	x=(x-1)*8;
	y=(y-1)*16;
	while((*chr>=' ')&&(*chr<='~'))
	{
		OLED_ShowChar(x,y,*chr);
		x+=8;
		if(x>112)
		{
			x=0;
			y+=16;
    }
		chr++;
  }
	OLED_Refresh();
}
void OLED_ShowInt(u8 x,u8 y,long int num,u8 len)
{
	u8 t,temp;	
	x=(x-1)*8;
	y=(y-1)*16;
	if(num<0)
	{
		OLED_ShowChar(x,y,'-');
		num=-num;
		x+=8;
	}
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(10,len-t-1))%10;
			if(temp==0)
				OLED_ShowChar(x+8*t,y,'0');
			else 
			  OLED_ShowChar(x+8*t,y,temp+'0');
  }
	OLED_Refresh();
}
void OLED_ShowFloat(u8 x,u8 y,double num,double len)
{
	unsigned char len1=len/1;
	int len2=(int)(len*10-len1*10);
	int num1;
	double num2;
	if(num<0)
	{
		OLED_ShowChar((x-1)*8,(y-1)*16,'-');
		x++;		
		num=-num;
	}
	num+=0.0000000001;
	num1=(int)num;
	num2=num-num1;
	OLED_ShowInt(x,y,num1,len1);
	num1=0;
	x=(x+len1-1)*8;
	y=(y-1)*16;
	OLED_ShowChar(x,y,'.');
	x+=8;
	num2*=OLED_Pow(10,len2);
	num1+=num2;
	OLED_ShowInt(x/8+1,y/16+1,num1,len2);
}
void OLED_ShowChineseStr(u8 x,u8 y,u8* str)
{
	int OLED_Chinese_size;
	u8 i,j;
	x=(x-1)*8;
	y=(y-1)*16;
	OLED_Chinese_size=strlen(str)/2;                              
	for(i=0;i<OLED_Chinese_size;i++)                                    
		for(j=0;i<=OLED_Chinese_Size+1;j++)                                 
	{ 
		if(str[i*2]==Chinese[j].Index[0]&&str[i*2+1]==Chinese[j].Index[1])         
		{
			OLED_ShowChinese(x,y,Chinese[j].num);                         
			x+=16;                                    
			break;
		}
		else if(j==OLED_Chinese_Size)                          
		{
			OLED_ShowChar(x,y,'?');
			x+=16;
			break;
		}
	}
}
void OLED_DrowFrame(u8 x1,u8 y1,u8 x2,u8 y2)
{
	OLED_DrawLine(x1,y1,x1,y2);
	OLED_DrawLine(x1,y1,x2,y1);
	OLED_DrawLine(x2,y1,x2,y2);
	OLED_DrawLine(x1,y2,x2,y2);	
}
void OLED_Init(void)
{
	uint32_t time;
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_14|GPIO_Pin_15;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	OLED_RST_Set();
	for(time=1000;time>0;time--);
	OLED_RST_Clr(); 
	for(time=1000;time>0;time--);
	OLED_RST_Set();
	
	OLED_WR_Byte(0xAE,OLED_CMD); 
	OLED_WR_Byte(0x00,OLED_CMD); 
	OLED_WR_Byte(0x10,OLED_CMD); 
	OLED_WR_Byte(0x40,OLED_CMD); 
	OLED_WR_Byte(0x81,OLED_CMD); 
	OLED_WR_Byte(0xCF,OLED_CMD); 
	OLED_WR_Byte(0xA1,OLED_CMD); 
	OLED_WR_Byte(0xC8,OLED_CMD); 
	OLED_WR_Byte(0xA6,OLED_CMD); 
	OLED_WR_Byte(0xA8,OLED_CMD); 
	OLED_WR_Byte(0x3f,OLED_CMD); 
	OLED_WR_Byte(0xD3,OLED_CMD); 
	OLED_WR_Byte(0x00,OLED_CMD); 
	OLED_WR_Byte(0xd5,OLED_CMD); 
	OLED_WR_Byte(0x80,OLED_CMD); 
	OLED_WR_Byte(0xD9,OLED_CMD); 
	OLED_WR_Byte(0xF1,OLED_CMD); 
	OLED_WR_Byte(0xDA,OLED_CMD); 
	OLED_WR_Byte(0x12,OLED_CMD);
	OLED_WR_Byte(0xDB,OLED_CMD); 
	OLED_WR_Byte(0x40,OLED_CMD); 
	OLED_WR_Byte(0x20,OLED_CMD); 
	OLED_WR_Byte(0x02,OLED_CMD); 
	OLED_WR_Byte(0x8D,OLED_CMD); 
	OLED_WR_Byte(0x14,OLED_CMD); 
	OLED_WR_Byte(0xA4,OLED_CMD); 
	OLED_WR_Byte(0xA6,OLED_CMD); 
	OLED_WR_Byte(0xAF,OLED_CMD);
	OLED_Clear();
	OLED_WR_Byte(0xA6,OLED_CMD);                                           
	OLED_WR_Byte(0xC8,OLED_CMD);                                            
	OLED_WR_Byte(0xA1,OLED_CMD);
	OLED_Refresh();
}
