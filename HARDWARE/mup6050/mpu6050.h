#ifndef _mpu6050_h_
#define _mpu6050_h_
void  InitMPU6050(void);													//初始化MPU6050
void Balance_filter(void);													//互补滤波
extern float  angle;														//外部变量，PID（）会调用互补滤波后的角度值
extern float  temp_Gry_x;												//陀螺仪读数，PID（）
#endif
