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

/////////////////PID����////////////////////////////////////////////////////
//����
float  Pc  = 0.1 	; //0.6//0.1		     �� 0.05	 �����ȶ�0.1		   
float  Ic  = 0.03 ;	//0.08					      0.04			   0.03		   
float  Dc  = 0		;
//�ٶ�
float  Ps  = 1.2 	; //17.92//0.2//0.5 	       0.3			       0.8
float  Is  = 0.02	;	//0.01//0.1//0//0.01	       0.1			   0.01
float  Ds  = 0   	; //4.48//0

//Ҫд�뵽STM32 FLASH���ַ�������
u8 Flash_PID[]={1,2,3,4,5,6};
u8 PID_Buffer[6] = {0};

void System_Init(void)
{
		delay_init();		  	 				//��ʱ��ʼ��
		NVIC_Configuration(); 	 		//����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
		Adc_Init();				 					//adc
		PID_init();
	  Flash_Save();								// ����Flash
		TIM4_Int_Init(99, 7199);	  //10Khz�ļ���Ƶ�ʣ�������5000Ϊ500ms  �ɼ��ٶȺ͵�������ֵ �����ռ�ձ�
		TIM3_PWM_Init(7199,0);		  //����Ƶ 72M ����7200Ϊ10K  PWM���       72000000 / 7200 = 10K = 0.1ms
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














