#ifndef __PID_H
#define __PID_H

#include "delay.h"
#include "stm32f10x.h"



#define initial_lue 1000   ////////����������������ʼֵ ����ֵ2.5/3.3*4096=3103  


#define D_MAX 2900
#define D_MIN 0 
#define I_MAX 800
#define I_MIN 0 
//����PID
typedef struct PID		
{
	int setpulse;		    //�趨ֵ
  int backpulse;			//����ֵ
	int last_error;  	
	int pre_error;
	//int u;		
	float P;		    	
	float I;		    
	float D;		    						
	int motorout;	  		//����������ֵ	
}PID;

extern PID PID_SpeedLoop;
void PID_init(void);
unsigned int C_PIDCalc( PID *pp );		//current
unsigned int S_PIDCalc( PID *pp );		//speed
float PIDCalc_FeedBackloop( PID *pp );
extern PID C_PID;
extern PID S_PID;
extern int Direction;
#endif
//