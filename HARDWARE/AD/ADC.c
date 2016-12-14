#include "ADC.h"
#include "delay.h"
/********************************************************************
文件名称：ADC模块
文件说明：
ADC模块初始化  DMA方式
这里使用了ADC1 的2个通道  1&2
对应引脚GPIOA_1 GPIOA_2

*******************************************************************/



uint16_t AD_C[2];

/***************************************************
函数名称：ADC模块初始化函数
入口参数：无
出口参数：无
函数说明：
初始化ADC模块，开启2个通道
1>ADC1  DMA 时钟
2>GPIO初始化   PA1  PA2   模拟输入方式
3>DMA配置  源地址  ADC1_DR_adress   目的地址  AD_C[2]
4>ADC配置  开启通道1  2

**************************************************/
int Adc_Init()
{
//1结构体声明
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef ADC_IN;
	DMA_InitTypeDef DMA_InitStructure;
//2开启时钟	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	 

//3GPIO初始化
	ADC_IN.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	ADC_IN.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOA, &ADC_IN);	
//DMA复位	
	DMA_DeInit(DMA1_Channel1);   
//4DMA初始化
	//地址配置  源地址  目的地址
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_adress;  
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_C;
	//模式设置   字节数   源地址自增  目的地址自增
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_adress;  //DMA外设基地址
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_C;					//&AD_C;//&cmar;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  				//数据传输方向，从外设读取发送到内存
	DMA_InitStructure.DMA_BufferSize = 2;  											//DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  					//内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; 				 //数据宽度为16位
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  							//工作在循环模式
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;					 	//DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  								//DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  								//根据DMA_InitStruct中指定的参数初始化DMA的通道adc所标识的寄存器
	DMA_Cmd(DMA1_Channel1, ENABLE);

	ADC_DeInit(ADC1);  //ADC1复位
//5ADC初始化
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC工作模式:ADC1和ADC2工作在独立模式
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//模数转换工作在单通道模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//模数转换工作源多次转换模式
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//转换由软件而不是外部触发启动
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC数据右对齐12位数据存储在16位内存中
	ADC_InitStructure.ADC_NbrOfChannel = 2;	//顺序进行规则转换的ADC通道的数目
	ADC_Init(ADC1, &ADC_InitStructure);	//根据ADC_InitStruct中指定的参数初始化外设ADCx的寄存器   
	

	
	/*配置ADC时钟，为PCLK2的8分频，即9Hz*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	/*配置ADC1的通道11为55.	5个采样周期，序列为1 */ 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_55Cycles5);
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	//矫正ADC
	ADC_ResetCalibration(ADC1);	//使能复位校准   
	while(ADC_GetResetCalibrationStatus(ADC1));	//等待复位校准结束
	ADC_StartCalibration(ADC1);	 //开启AD校准
	while(ADC_GetCalibrationStatus(ADC1));	 //等待校准结束
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//使能指定的ADC1的软件转换启动功能
	return 1;
}

