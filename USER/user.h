#ifndef __user_H
#define __user_H

#include "stm32f10x.h"
#define FLASH_SAVE_ADDR  0X08010000 						//����FLASH �����ַ(����Ϊż��������ֵҪ���ڱ�������ռ��FLASH�Ĵ�С+0X08000000)
extern u8 PID_Buffer[6];
void System_Init(void);
void WIN_SHOW(void);	
void Flash_Save(void);
/////////////////PID����////////////////////////////////////////////////////
extern float  Pc;     
extern float  Ic; 
extern float  Dc; 
extern float  Ps;  
extern float  Is;  
extern float  Ds;     


#endif

