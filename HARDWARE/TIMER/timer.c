#include "timer.h"
#include "pid.h"
#include "LCD5110.h"
#include "adc.h"
u32 count_val   = 0;   //����ֵ
float Open_PWM  = 0;
u16 adc1 			  = 0;
u16 adc2 				= 0;
//ͨ�ö�ʱ��4�жϳ�ʼ����
//����ʱ��ѡ��ΪAPB1��2������APB1Ϊ36M
//arr���Զ���װֵ�� 99
//psc��ʱ��Ԥ��Ƶ�� 7199   72000000 / 7200  = 10K = 0.1ms  7200 / 72000000 = 0.1 ms  ������5000Ϊ500ms  �˳�����10msһ���ж�
//����ʹ�õ��Ƕ�ʱ��4!
void TIM4_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 					//ʱ��ʹ��
	//��ʱ��TIM4��ʼ��
	TIM_TimeBaseStructure.TIM_Period = arr; 											//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 										//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 			//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 							//����ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); 										//ʹ��ָ����TIM3�ж�,��������ж�

	//�ж����ȼ�NVIC����
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  							//TIM4�ж�
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//��ռ���ȼ�0��
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  					//�����ȼ�3��
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 							//IRQͨ����ʹ��
	NVIC_Init(&NVIC_InitStructure);  															//��ʼ��NVIC�Ĵ���

	TIM_Cmd(TIM4, ENABLE);  																			//ʹ��TIMx					 
}
//��ʱ��4�жϷ������
void TIM4_IRQHandler(void)   																		//TIM4�ж�
{											   																				//�⺯����RESET��5110�ж����RESET��ͻ
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET )						//RESET) //���TIM3�����жϷ������
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  							//���TIMx�����жϱ�־ 
	}
	
	
	
  #ifdef OPEN																										//����
		PWM_Set_Duty = Open_PWM;
	#else					
		S_PID.backpulse = AD_C[0];																	//�ջ�
		PWM_Set_Duty = S_PIDCalc(&S_PID) + 3600;
	#endif
}
//
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);									//ʹ�ܶ�ʱ��3ʱ��
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  , ENABLE);  							//ʹ��GPIOAģ��ʱ��
	  
 
  //���ø�����Ϊ�����������,���TIM3_CH1��PWM���岨��	GPIOA.6
	GPIO_InitStructure.GPIO_Pin 		= GPIO_Pin_6; 												//TIM3_CH1
	GPIO_InitStructure.GPIO_Mode		= GPIO_Mode_AF_PP;  									//�����������
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);																//��ʼ��GPIO
 
  //��ʼ��TIM3
	TIM_TimeBaseStructure.TIM_Period 				= arr; 												//��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler 		= psc; 												//����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 													//����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;   			//TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 											//����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ
	
	//��ʼ��TIM3 Channel2 PWMģʽ	 
	TIM_OCInitStructure.TIM_OCMode			 		= TIM_OCMode_PWM2; 						//ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ2
 	TIM_OCInitStructure.TIM_OutputState 		= TIM_OutputState_Enable; 		//�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_OCPolarity 			= TIM_OCPolarity_High; 				//�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  														//����Tָ���Ĳ�����ʼ������TIM3 OC1

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  										//ʹ��TIM3��CCR1�ϵ�Ԥװ�ؼĴ���
 	//���������е�OC1ȷ������channle����Ҫ��OC2����channel 2  						//Ĭ��TIM3->CCR1��3600
	TIM3->CCR1 = arr/2;	    																							//��ʼ��ռ�ձ� ֻҪ�ı���CCR1����ֵ�Ϳ��Ըı�ռ�ձ�

	TIM_Cmd(TIM3, ENABLE);  																							//ʹ��TIM3
}
//

