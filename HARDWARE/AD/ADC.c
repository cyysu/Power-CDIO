#include "ADC.h"
#include "delay.h"
/********************************************************************
�ļ����ƣ�ADCģ��
�ļ�˵����
ADCģ���ʼ��  DMA��ʽ
����ʹ����ADC1 ��2��ͨ��  1&2
��Ӧ����GPIOA_1 GPIOA_2

*******************************************************************/



uint16_t AD_C[2];

/***************************************************
�������ƣ�ADCģ���ʼ������
��ڲ�������
���ڲ�������
����˵����
��ʼ��ADCģ�飬����2��ͨ��
1>ADC1  DMA ʱ��
2>GPIO��ʼ��   PA1  PA2   ģ�����뷽ʽ
3>DMA����  Դ��ַ  ADC1_DR_adress   Ŀ�ĵ�ַ  AD_C[2]
4>ADC����  ����ͨ��1  2

**************************************************/
int Adc_Init()
{
//1�ṹ������
	ADC_InitTypeDef ADC_InitStructure; 
	GPIO_InitTypeDef ADC_IN;
	DMA_InitTypeDef DMA_InitStructure;
//2����ʱ��	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA |RCC_APB2Periph_ADC1	, ENABLE );	 

//3GPIO��ʼ��
	ADC_IN.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2;
	ADC_IN.GPIO_Mode = GPIO_Mode_AIN;		
	GPIO_Init(GPIOA, &ADC_IN);	
//DMA��λ	
	DMA_DeInit(DMA1_Channel1);   
//4DMA��ʼ��
	//��ַ����  Դ��ַ  Ŀ�ĵ�ַ
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_adress;  
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_C;
	//ģʽ����   �ֽ���   Դ��ַ����  Ŀ�ĵ�ַ����
	DMA_InitStructure.DMA_PeripheralBaseAddr = ADC1_DR_adress;  //DMA�������ַ
	DMA_InitStructure.DMA_MemoryBaseAddr = (u32)&AD_C;					//&AD_C;//&cmar;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  				//���ݴ��䷽�򣬴������ȡ���͵��ڴ�
	DMA_InitStructure.DMA_BufferSize = 2;  											//DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  					//�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; 				 //���ݿ��Ϊ16λ
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;  							//������ѭ��ģʽ
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;					 	//DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  								//DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);  								//����DMA_InitStruct��ָ���Ĳ�����ʼ��DMA��ͨ��adc����ʶ�ļĴ���
	DMA_Cmd(DMA1_Channel1, ENABLE);

	ADC_DeInit(ADC1);  //ADC1��λ
//5ADC��ʼ��
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;	//ADC����ģʽ:ADC1��ADC2�����ڶ���ģʽ
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;	//ģ��ת�������ڵ�ͨ��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;	//ģ��ת������Դ���ת��ģʽ
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;	//ת��������������ⲿ��������
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;	//ADC�����Ҷ���12λ���ݴ洢��16λ�ڴ���
	ADC_InitStructure.ADC_NbrOfChannel = 2;	//˳����й���ת����ADCͨ������Ŀ
	ADC_Init(ADC1, &ADC_InitStructure);	//����ADC_InitStruct��ָ���Ĳ�����ʼ������ADCx�ļĴ���   
	

	
	/*����ADCʱ�ӣ�ΪPCLK2��8��Ƶ����9Hz*/
	RCC_ADCCLKConfig(RCC_PCLK2_Div8); 
	/*����ADC1��ͨ��11Ϊ55.	5���������ڣ�����Ϊ1 */ 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 2, ADC_SampleTime_55Cycles5);
	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);
	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);
	//����ADC
	ADC_ResetCalibration(ADC1);	//ʹ�ܸ�λУ׼   
	while(ADC_GetResetCalibrationStatus(ADC1));	//�ȴ���λУ׼����
	ADC_StartCalibration(ADC1);	 //����ADУ׼
	while(ADC_GetCalibrationStatus(ADC1));	 //�ȴ�У׼����
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);		//ʹ��ָ����ADC1�����ת����������
	return 1;
}

