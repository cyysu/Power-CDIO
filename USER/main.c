#include "include.h"				// FIRMWARE
#include "cmsis_os.h"       // ARM::CMSIS:RTOS:Keil RTX
//������ջ����ܿ��ƿ��� 
#define OPEN
/******************************************************************

File name	:    CDIO_Test
Author		:    Version: V4.0  Date: 2016.6.2


CDIO_NUMBER	:    6
CDIO_MEMBER	:    ���������Դ��������������
           	     ��ʥ������溡��������ΰ


History:
�޶�ʱ�䣺2016.5.30
1>ADC�޸�ΪDMAģʽ   PA_1  PA_2
2>��ֵ�˲�������ɾȥ�ˣ���Ҫʱ�ٲ��ϡ�
3>PID���򲿷����������޸�
4>����δ����5110��ʾ���� 

Message:
1>PID������ҪȥPID.H�ļ��޸�
2>��������ʵ�ּӼ��ٽ�Ծ����

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
