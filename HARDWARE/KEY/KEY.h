#ifndef __KEY_H
#define __KEY_H
#include "sys.h"
#include "pid.h"

#define KEY0  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_10)//读取按键0
#define KEY1  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_11)//读取按键1
#define KEY2  GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_12)//读取按键2 
#define KEY3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//读取按键3 
#define KEY4  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_5)//读取按键4 
#define KEY5  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_6)//读取按键5 

//上
#define KEY_UP    1
//下
#define KEY_DOWN  2
//左
#define KEY_LEFT  3
//右
#define KEY_RIGHT 4
//确定
#define SURE			0

extern u16 Fun_KEY;
extern u8 KEY_FUN;

void KEY_Scan(u8 mode);


extern int setvalue;
extern PID S_PID;
extern u16 KeyBoard;
void KEY_Init(void);	//IO初始化
void KEY_Scan(u8 mode);  	//按键扫描函数	

#endif
