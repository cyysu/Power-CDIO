#ifndef __ADC_H
#define __ADC_H

#include "stm32f10x.h"
#include "delay.h"
#include "stm32f10x_adc.h"
#include "stm32f10x_dma.h"

extern uint16_t AD_C[2];

#define ADC1_DR_adress ((u32)0x40012400+0x4c)   //ADC地址

int Adc_Init(void);//ADC初始化函数

#endif
