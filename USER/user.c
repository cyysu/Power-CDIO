#include "stm32f10x.h"
#include "timer.h"
#include "LCD5110.h"
#include "ADC.h"
#include "stmflash.h"
#include "pid.h"
#include "KEY.h"
#include "math.h"
#include "speed.h"
#include "user.h"
#include "gui.h"

/////////////////PID调节////////////////////////////////////////////////////
//电流
float  Pc  = 0.1 	; //0.6//0.1		     振荡 0.05	 振荡至稳定0.1		   
float  Ic  = 0.03 ;	//0.08					      0.04			   0.03		   
float  Dc  = 0		;
//速度
float  Ps  = 1.2 	; //17.92//0.2//0.5 	       0.3			       0.8
float  Is  = 0.02	;	//0.01//0.1//0//0.01	       0.1			   0.01
float  Ds  = 0   	; //4.48//0

//要写入到STM32 FLASH的字符串数组
u8 Flash_PID[]={1,2,3,4,5,6};
u8 PID_Buffer[6] = {0};

void System_Init(void)
{
		delay_init();		  	 				//延时初始化
		NVIC_Configuration(); 	 		//设置NVIC中断分组2:2位抢占优先级，2位响应优先级
		Adc_Init();				 					//adc
		PID_init();
	  Flash_Save();								// 存入Flash
		TIM4_Int_Init(99, 7199);	  //10Khz的计数频率，计数到5000为500ms  采集速度和电流反馈值 并求得占空比
		TIM3_PWM_Init(7199,0);		  //不分频 72M 计数7200为10K  PWM输出       72000000 / 7200 = 10K = 0.1ms
		KEY_Init();
		InitLcd();
		Boot_Menu();
		Boot_Menu_System();
}  

void Flash_Save(void)
{
		STMFLASH_Write(FLASH_SAVE_ADDR,(u16*)Flash_PID,6);		
		STMFLASH_Read(FLASH_SAVE_ADDR,(u16*)PID_Buffer,6);
}














