#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include "stm32f10x.h"
#include "timer.h"
#include "LCD5110.h"
#include "ADC.h"
#include "pid.h"
#include "KEY.h"
#include "math.h"
#include "speed.h"
#include "user.h"
#include "gui.h"
#endif
//
//	����io��
//  GPIO_InitTypeDef  GPIO_InitStructure;	 
// 	
//  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��PB,PE�˿�ʱ��
//	
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_0|GPIO_Pin_1;//PA 0167 �˿�����
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
//  GPIO_Init(GPIOA, &GPIO_InitStructure);					 //
//
//  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;//PA 0167 �˿�����
//  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
//  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 //IO���ٶ�Ϊ50MHz
//  GPIO_Init(GPIOB, &GPIO_InitStructure);					 //�����趨������ʼ��GPIOB.5  
//  while(1)
//	{
//	  GPIO_ResetBits(GPIOA,GPIO_Pin_6);
//	  GPIO_SetBits(GPIOA,GPIO_Pin_7);
//		GPIO_SetBits(GPIOA,GPIO_Pin_0);
//		GPIO_SetBits(GPIOA,GPIO_Pin_1);
//		GPIO_SetBits(GPIOB,GPIO_Pin_6);
//		GPIO_SetBits(GPIOB,GPIO_Pin_7);
//		GPIO_SetBits(GPIOB,GPIO_Pin_8);
//		GPIO_SetBits(GPIOB,GPIO_Pin_9);
//		Delay(3000000);
//		GPIO_SetBits(GPIOA,GPIO_Pin_6);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_7);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_0);
//		GPIO_ResetBits(GPIOA,GPIO_Pin_1);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_6);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_7);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_8);
//		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
//		Delay(3000000);
//	}


