#include "KEY.h"
#include "stm32f10x.h"
#include "sys.h" 
#include "delay.h"
#include "timer.h"
#include "LCD5110.h"
#include "pid.h"

int setvalue = 0;
u16 KeyBoard = 0;
u16 Fun_KEY;
u8  KEY_FUN;
//按键初始化函数
void KEY_Init(void) //IO初始化
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
	//初始化KEY0-->GPIOA.13,KEY1-->GPIOA.15  上拉输入
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE);//使能PORTB,PORTC,PORTD时钟
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_5|GPIO_Pin_6;			//PE5/6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 						//设置成上拉输入
 	GPIO_Init(GPIOB, &GPIO_InitStructure);										//初始化GPIOE5,6
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;//PC10/11/12
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 						//设置成上拉输入
 	GPIO_Init(GPIOC, &GPIO_InitStructure);										//初始化GPIOE10,11,12
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_2;								//PE5/6
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 						//设置成上拉输入
 	GPIO_Init(GPIOD, &GPIO_InitStructure);										//初始化GPIOD2
}
//按键处理函数
//返回按键值
//mode:0,不支持连续按;1,支持连续按;
//0，没有任何按键按下
//1，KEY0按下
//2，KEY1按下
//3，KEY2按下 
//4，KEY3按下 WK_UP
//注意此函数有响应优先级,KEY0>KEY1>KEY2>KEY3!!
// 键盘扫描
/**
void KEY_Scan(u8 mode)
{
	if(setvalue>2900)					//最大占空比限制为83%
		setvalue=2900;		  
	
	if(!(GPIOC->IDR&GPIO_Pin_10))
	{
			delay_ms(50);
			if(!(GPIOC->IDR&GPIO_Pin_10))
			{
					if(KEY_FUN == 0)
						KeyBoard = 1;	
					else
						setvalue+=72;
			}		
	}
	if(!(GPIOC->IDR&GPIO_Pin_11)) 
	{
			if(KEY_FUN == 0)
					KeyBoard = 2;	
			else
					setvalue+=36;
	}
	if(!(GPIOC->IDR&GPIO_Pin_12)) 
	{
			if(KEY_FUN == 0)
				KeyBoard = 3;
			else
				setvalue-=36;			
	}
	if(!(GPIOD->IDR&GPIO_Pin_2)) 
	{
			if(KEY_FUN == 0)
				KeyBoard = 4;	
			else
				setvalue-=72;

	}
	if(!(GPIOB->IDR&GPIO_Pin_5)) 
	{
			delay_ms(50);
			if(!(GPIOB->IDR&GPIO_Pin_5)) 
			{
				if(KEY_FUN == 0)
				{
						Fun_KEY = 1;
						KeyBoard = 0;	
				}
				else
				{
						Open_PWM = setvalue + 3600;
						setvalue = 0;
				}
			}	
	}
	if(!(GPIOB->IDR&GPIO_Pin_6)) 
	{
			KEY_FUN = !KEY_FUN;
	}
}**/

void KEY_Scan(u8 mode)
{	 
	static u8 key_up=1;				//按键按松开标志
	if(mode)key_up=1;  				//支持连按
	if(setvalue>2900)					//最大占空比限制为83%
	setvalue=2900;		  
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||KEY3==1))
	{
			delay_ms(200);					//去抖动 
			key_up=0;
			if(KEY0==0)
			{
					if(KEY_FUN == 0)
						KeyBoard = 1;	
					else
						setvalue+=72;
			}
			else if(KEY1==0)
			{
				if(KEY_FUN == 0)
					KeyBoard = 2;	
				else
						setvalue+=36;
			}
			else if(KEY2==0)
			{				
				if(KEY_FUN == 0)
					KeyBoard = 3;
				else
					setvalue-=36;				

			}
		  else if(KEY3==0)
			{
				if(KEY_FUN == 0)
					KeyBoard = 4;	
				else
					setvalue-=72;

			}
		  else if(KEY4==0)			//送出给定值+清零
			{		
					if(KEY_FUN == 0)
					{
						Fun_KEY = 1;
						KeyBoard = 0;	
					}
					else
					{
							#ifdef OPEN
								Open_PWM = setvalue + 3600;
							#else
								S_PID.setpulse = setvalue;
							#endif
							setvalue = 0;
					}
			}
		  else if(KEY5==0)			//按键功能
			{		
					KEY_FUN = !KEY_FUN;
			}
	}
	else if(KEY0==1&&KEY1==1&&KEY2==1&&KEY3==1&&KEY5==1)
			key_up=1;							//无按键按下 	    
}
//

