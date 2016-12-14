#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
#include "pid.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)//��ȡ����1
#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)//��ȡ����2 
#define KEY3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//��ȡ����3 
#define KEY4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//��ȡ����4 
#define KEY5  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//��ȡ����5 

//��
#define KEY_UP    1
//��
#define KEY_DOWN  2
//��
#define KEY_LEFT  3
//��
#define KEY_RIGHT 4
//ȷ��
#define SURE			0

extern u16 Fun_KEY;
extern u8 KEY_FUN;

void KEY_Scan(u8 mode);


extern int setvalue;
extern PID S_PID;
extern u16 KeyBoard;
void KEY_Init(void);	//IO��ʼ��
void KEY_Scan(u8 mode);  	//����ɨ�躯��	

#endif
