#ifndef _mpu6050_h_
#define _mpu6050_h_
void  InitMPU6050(void);													//��ʼ��MPU6050
void Balance_filter(void);													//�����˲�
extern float  angle;														//�ⲿ������PID��������û����˲���ĽǶ�ֵ
extern float  temp_Gry_x;												//�����Ƕ�����PID����
#endif
