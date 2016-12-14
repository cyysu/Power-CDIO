#include "timer.h"
#include "pid.h"
#include "LCD5110.h"
#include "adc.h"
u32 count_val   = 0;   //计数值
float Open_PWM  = 0;
u16 adc1 			  = 0;
u16 adc2 				= 0;
//通用定时器4中断初始化·
//这里时钟选择为APB1的2倍，而APB1为36M
//arr：自动重装值。 99
//psc：时钟预分频数 7199   72000000 / 7200  = 10K = 0.1ms  7200 / 72000000 = 0.1 ms  计数满5000为500ms  此程序是10ms一次中断
//这里使用的是定时器4!
void TIM4_Int_Init(u16 arr,u16 psc)
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE); 					//时钟使能
	//定时器TIM4初始化
	TIM_TimeBaseStructure.TIM_Period = arr; 											//设置在下一个更新事件装入活动的自动重装载寄存器周期的值	
	TIM_TimeBaseStructure.TIM_Prescaler =psc; 										//设置用来作为TIMx时钟频率除数的预分频值
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 			//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	//TIM向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 							//根据指定的参数初始化TIMx的时间基数单位
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE ); 										//使能指定的TIM3中断,允许更新中断

	//中断优先级NVIC设置
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn;  							//TIM4中断
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;  		//先占优先级0级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;  					//从优先级3级
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 							//IRQ通道被使能
	NVIC_Init(&NVIC_InitStructure);  															//初始化NVIC寄存器

	TIM_Cmd(TIM4, ENABLE);  																			//使能TIMx					 
}
//定时器4中断服务程序
void TIM4_IRQHandler(void)   																		//TIM4中断
{											   																				//库函数中RESET与5110中定义的RESET冲突
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET )						//RESET) //检查TIM3更新中断发生与否
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update  );  							//清除TIMx更新中断标志 
	}
	
	
	
  #ifdef OPEN																										//开环
		PWM_Set_Duty = Open_PWM;
	#else					
		S_PID.backpulse = AD_C[0];																	//闭环
		PWM_Set_Duty = S_PIDCalc(&S_PID) + 3600;
	#endif
}
//
void TIM3_PWM_Init(u16 arr,u16 psc)
{  
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);									//使能定时器3时钟
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA  , ENABLE);  							//使能GPIOA模块时钟
	  
 
  //设置该引脚为复用输出功能,输出TIM3_CH1的PWM脉冲波形	GPIOA.6
	GPIO_InitStructure.GPIO_Pin 		= GPIO_Pin_6; 												//TIM3_CH1
	GPIO_InitStructure.GPIO_Mode		= GPIO_Mode_AF_PP;  									//复用推挽输出
	GPIO_InitStructure.GPIO_Speed 	= GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);																//初始化GPIO
 
  //初始化TIM3
	TIM_TimeBaseStructure.TIM_Period 				= arr; 												//设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler 		= psc; 												//设置用来作为TIMx时钟频率除数的预分频值 
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; 													//设置时钟分割:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode 	= TIM_CounterMode_Up;   			//TIM向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 											//根据TIM_TimeBaseInitStruct中指定的参数初始化TIMx的时间基数单位
	
	//初始化TIM3 Channel2 PWM模式	 
	TIM_OCInitStructure.TIM_OCMode			 		= TIM_OCMode_PWM2; 						//选择定时器模式:TIM脉冲宽度调制模式2
 	TIM_OCInitStructure.TIM_OutputState 		= TIM_OutputState_Enable; 		//比较输出使能
	TIM_OCInitStructure.TIM_OCPolarity 			= TIM_OCPolarity_High; 				//输出极性:TIM输出比较极性高
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  														//根据T指定的参数初始化外设TIM3 OC1

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  										//使能TIM3在CCR1上的预装载寄存器
 	//上面两句中的OC1确定了是channle几，要是OC2则是channel 2  						//默认TIM3->CCR1是3600
	TIM3->CCR1 = arr/2;	    																							//初始化占空比 只要改变了CCR1的数值就可以改变占空比

	TIM_Cmd(TIM3, ENABLE);  																							//使能TIM3
}
//

