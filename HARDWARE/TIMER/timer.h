#ifndef __TIMER_H
#define __TIMER_H
#include "sys.h"
#include "pid.h"	  

//ͨ���ı�TIM3->CCR1��ֵ���ı�ռ�ձȣ��Ӷ����Ƶ��ת��PWM_Set_Duty
#define PWM_Set_Duty TIM3->CCR1 

extern u16 adc1,adc2;
extern float Open_PWM;
extern PID C_PID;
extern PID S_PID;

void TIM3_PWM_Init(u16 arr,u16 psc);
void TIM4_Int_Init(u16 arr,u16 psc);


#endif























