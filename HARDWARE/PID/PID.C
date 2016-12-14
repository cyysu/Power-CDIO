#include "pid.h"
#include "ADC.h"
#include "LCD5110.h"
#include "math.h"
#include "user.h"
PID C_PID;
PID S_PID;
int Direction=0;

void PID_init(void)
{	
  	C_PID.setpulse = 0 ;	      	//电流设定值
  	C_PID.backpulse = 0 ;					//电流反馈值		
  	C_PID.last_error = 0 ;	 
  	C_PID.pre_error = 0 ;	  
  	C_PID.P = Pc;
  	C_PID.I = Ic;
  	C_PID.D = Dc;	
  	C_PID.motorout = 0 ;		    	//电机控制输出值

	  S_PID.setpulse = 0 ;	      	//速度设定值
  	S_PID.backpulse = 0 ;					//速度反馈值		
  	S_PID.last_error = 0 ;	 
  	S_PID.pre_error = 0 ;	  
  	S_PID.P = Ps;
  	S_PID.I = Is;
  	S_PID.D = Ds;
	//S_PID.u = 0;	
  	S_PID.motorout = 0 ;		    	//电流给定值
}

unsigned int S_PIDCalc( PID *pp )
{
  int error = 0;
	
  if(((int)AD_C[1]-2048) > 0 )				///检测电流的正负   调节电阻将占空比为50的时候设置成2048(电流中值)
		Direction =  1;
	else
		Direction = -1;
	
	error = pp->setpulse / 1.65 - Direction * pp->backpulse;	
  pp->motorout   += (int)(pp->P*(error-pp->last_error) + pp->I*error + pp->D*(error-2*pp->last_error+pp->pre_error));	
 	pp->pre_error  =  pp->last_error;	 
 	pp->last_error =  error;
    	
  if( pp->motorout >= I_MAX) 		
		   pp->motorout = I_MAX;		
  else if( pp->motorout <=I_MIN)	//速度PID，防止调节最低溢出 
		   pp->motorout = I_MIN;			
  	
  return (pp->motorout);					// 返回预调节电流值
}
 
