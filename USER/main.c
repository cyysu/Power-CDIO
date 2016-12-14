#include "include.h"				// FIRMWARE
#include "cmsis_os.h"       // ARM::CMSIS:RTOS:Keil RTX
//开环与闭环的总控制开关 
#define OPEN
/******************************************************************

File name	:    CDIO_Test
Author		:    Version: V4.0  Date: 2016.6.2


CDIO_NUMBER	:    6
CDIO_MEMBER	:    孟令军、陈源、张祖坤、王悦
           	     修圣虎、温婧、李晶、刘婷伟


History:
修订时间：2016.5.30
1>ADC修改为DMA模式   PA_1  PA_2
2>均值滤波环节先删去了，需要时再补上。
3>PID程序部分作出名称修改
4>程序未加入5110显示曲线 

Message:
1>PID参数需要去PID.H文件修改
2>按键可以实现加减速阶跃调控

Copyright(C) 	@2015 - 2016
******************************************************************/

int main(void)
{	
		System_Init();
		for(;;)
		{
				SystemMenu_GUI();
		}
}
//
