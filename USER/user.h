#ifndef __user_H
#define __user_H

#include "stm32f10x.h"
#define FLASH_SAVE_ADDR  0X08010000 						//设置FLASH 保存地址(必须为偶数，且其值要大于本代码所占用FLASH的大小+0X08000000)
extern u8 PID_Buffer[6];
void System_Init(void);
void WIN_SHOW(void);	
void Flash_Save(void);
/////////////////PID调节////////////////////////////////////////////////////
extern float  Pc;     
extern float  Ic; 
extern float  Dc; 
extern float  Ps;  
extern float  Is;  
extern float  Ds;     


#endif

