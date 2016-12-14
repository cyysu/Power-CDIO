#ifndef __speed_H
#define __speed_H

#include "stm32f10x.h"

extern u16 speed_collect[20];
extern u16 current_collect[20];
extern u16 speed_n,speed_x,speed_x1,speed_x2,speed_y,speed_y1,speed_y2;	
void Delay(u32 count);
#endif 

