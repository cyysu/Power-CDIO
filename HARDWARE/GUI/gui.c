#include "gui.h"
#include "KEY.h"
#include "LCD5110.h"
#include "user.h"
#include "adc.h"

int menu_Number = 0;
int menu_Number_Horizontal = 0;

int a = -13;

void Boot_Menu(void)
{
		u16 i;
		/*-------不使用buf画图和写字，速度最快，省内存----------------*/
		for(i = 0;i < 6;i++)
		{
				PutIcon((char*)(icon + i),i,0);
		}	
		LCD_set_XY(13,0);
		for(i = 0;i < 7;i++)
		{
				WriteIcon((char*)(icon + 15 + i));
		}	
		PutHanziStr((char*)Hanzi2,2,15,4);
		PutStr("C D I O",2,4);
		delay_ms(40000);
		BufClearAll();
		BufClearAll();
		LcdClearAll();
				
		delay_ms(40000);				//等待
		
		/*--------使用buf画图和写字(每一次操作自动刷新,速度最慢)----------*/
		BufClearAll();
		BufDrawBmp((char *)girl,0,0,45,48);
    PutStr(" Start..",4,6);
		delay_ms(40000);
		BufClearAll();	
		LcdClearAll();
		
}

void Menu_Select(void)
{
			if(Fun_KEY == 1) //表示是菜单选项
			{
					PutStr("Menu Start...",3,0);
			}
			else	// 参数设置
			{
					PutStr("Param Start...",3,0);
			}
}

void Boot_Menu_System(void)
{
	  // 系统
		LCD_set_XY(7,5);		
		WriteIcon((char*)(icon + 19));	
		// 曲线
		WriteIcon((char*)(icon + 35));	
	  WriteIcon((char*)(icon + 35));	
		WriteIcon((char*)(icon + 15));		
		// 音乐
		WriteIcon((char*)(icon + 35));	
	  WriteIcon((char*)(icon + 35));	
		WriteIcon((char*)(icon + 16));	
		
		PutStr("1. Open  Loop",0,1);
		PutStr("2. Close Loop",1,1);
		PutStr("3. Param Read",2,1);
		PutStr("4. Return    ",3,1);
	  PutStr(">",0,0);
		PutStr(">",5,0);
}

void Boot_Menu_Image(void)
{
		LcdClearAll();
		// 系统
		LCD_set_XY(7,5);		
		WriteIcon((char*)(icon + 19));	
		// 曲线
		WriteIcon((char*)(icon + 35));	
	  WriteIcon((char*)(icon + 35));	
		WriteIcon((char*)(icon + 15));		
		// 音乐
		WriteIcon((char*)(icon + 35));	
	  WriteIcon((char*)(icon + 35));	
		WriteIcon((char*)(icon + 16));	
	
		PutStr("1. Contact Us",0,1);
		PutStr("2. System Inf",1,1);
		PutStr("3. System Ver",2,1);
		PutStr("4. Return    ",3,1);
		PutStr(">",0,0);
	
}

void Boot_Menu_Music(void)
{
	  LcdClearAll();
		// 系统
		LCD_set_XY(7,5);		
		WriteIcon((char*)(icon + 19));	
		// 曲线
		WriteIcon((char*)(icon + 35));	
	  WriteIcon((char*)(icon + 35));	
		WriteIcon((char*)(icon + 15));		
		// 音乐
		WriteIcon((char*)(icon + 35));	
	  WriteIcon((char*)(icon + 35));	
		WriteIcon((char*)(icon + 16));	
	
		PutStr("    YSU      ",0,1);
		PutStr("    CDIO     ",1,1);
		PutStr("  Kali Linux ",2,1);
		PutStr("  2016-6-18  ",3,1);
}

void menu_Select_V(void)
{
	 if(menu_Number == 0){
			PutStr(">",0,0);
			PutStr(" ",1,0);
			PutStr(" ",2,0);
			PutStr(" ",3,0);
	 }else if(menu_Number == 1)
	 {
			PutStr(" ",0,0);
			PutStr(">",1,0);
			PutStr(" ",2,0);
			PutStr(" ",3,0);	
	 }else if(menu_Number == 2){
			PutStr(" ",0,0);
			PutStr(" ",1,0);
		 	PutStr(">",2,0);
			PutStr(" ",3,0);
	 }else if(menu_Number == 3){
			PutStr(" ",0,0);
			PutStr(" ",1,0);
			PutStr(" ",2,0);
			PutStr(">",3,0);
	 }
}

void menu_select_H(void)
{
	 if(menu_Number_Horizontal == 0){
		  Boot_Menu_System();
		  PutStr(">",5,0);
			PutStr(" ",5,5);
			PutStr(" ",5,10);
	 }else if(menu_Number_Horizontal == 1)
	 {
		  Boot_Menu_Image();
		  PutStr(" ",5,0);
			PutStr(">",5,5);
			PutStr(" ",5,10);
	 }else if(menu_Number_Horizontal == 2){
		  Boot_Menu_Music();
		  PutStr(" ",5,0);
			PutStr(" ",5,5);
			PutStr(">",5,10);
	 }
}

//显示系统
void SystemMenu_GUI(void)
{	
		KEY_Scan(0);	
		SystemMenu();
		SystemSonMenu();
}
//显示菜单
void SystemMenu(void)
{
	 if(KeyBoard == KEY_LEFT)
		{
				// 菜单单项进行向左移动
			  KeyBoard = 0;
				menu_Number_Horizontal--;
			  if(menu_Number_Horizontal<0)
					menu_Number_Horizontal = 2;
				LcdClearAll();
				menu_select_H();
		}
		if(KeyBoard == KEY_RIGHT)
		{
				// 菜单单项进行向右移动
			  KeyBoard = 0;
				menu_Number_Horizontal++;
			  if(menu_Number_Horizontal>2)
					menu_Number_Horizontal = 0;
				LcdClearAll();
				menu_select_H();
		}	
}
//显示系统子菜单
void SystemSonMenu(void)
{
		//子菜单上移
		if(KeyBoard == KEY_UP)
		{
			 KeyBoard = 0;
			 menu_Number--;
			 if(menu_Number < 0)
				 menu_Number = 3;
			 menu_Select_V();

		}//子菜单下移
		else if(KeyBoard == KEY_DOWN)
		{ 
			 KeyBoard = 0;
			 menu_Number++;
			 if(menu_Number > 3)
				 menu_Number = 0;
			 menu_Select_V(); 
		}		
		 ///判断确定按键是否按下
		 if(Fun_KEY)
		 {
			  Fun_KEY = 0;
			 	LcdClearAll();
				for(;;)
				{
						if(menu_Number_Horizontal == 0)
						{
									if(menu_Number ==0)
									{
											Fun_KEY = 0;
											for(;;)
											{
													KEY_Scan(0);	
													/*  1-3 显示汉字  4 不显示汉字
															1. 显示转速      xx
															2. 显示电流      xx
															3. 显示占空比    xx
															4. 按键值        xx
													*/
													//PutHanziStr((char*)Hanzi5,1,15,4);	///开环测试界面
												  //delay_ms(4000);
													//delay_ms(4000);
													//LcdClearAll();
													PutHanziStr((char*)Hanzi10,0,6,1);	///转速
													LCD_Write_Num(28,0,AD_C[0],4);
												
													PutHanziStr((char*)Hanzi11,1,4,1);	///电流
													LCD_Write_Num(28,3,AD_C[1],4);
												
													PutHanziStr((char*)Hanzi12,2,4,1);	///占空比
													LCD_Write_Num(28,5,PWM_Set_Duty/72,4);
														
													//这里需要判断正负给定并显示符号    ///显示键盘给定值
													if(setvalue < 0)
													{
															PutStr("-",5,11);
															LCD_Write_Num(72,5,(-setvalue)/36,2);	
													}	
													else
													{
															PutStr(" ",5,11);	
															LCD_Write_Num(72,5,setvalue/36,2);	
													}	
												  delay_ms(50);
													if(Fun_KEY)
													{
															Fun_KEY = 0;
															LcdClearAll();
															PutHanziStr((char*)Hanzi8,1,17,2);	///返回界面
															delay_ms(4000);
															LcdClearAll();
															Boot_Menu_System();
															return;
													}	
											}											
									}		
									else if(menu_Number == 1)
									{
											Fun_KEY = 0;
											for(;;)
											{
													KEY_Scan(0);	
													/*  1-3 显示汉字  4 不显示汉字
															1. 显示转速      xx
															2. 显示电流      xx
															3. 显示占空比    xx
															4. 按键值        xx
													*/
													//PutHanziStr((char*)Hanzi5,1,15,4);	///闭环测试界面
												  //delay_ms(4000);
													//delay_ms(4000);
													//LcdClearAll();
													PutHanziStr((char*)Hanzi10,0,6,1);	///转速
													LCD_Write_Num(28,0,AD_C[0],4);
												
													PutHanziStr((char*)Hanzi11,1,4,1);	///电流
													LCD_Write_Num(28,3,AD_C[1],4);
												
													PutHanziStr((char*)Hanzi12,2,4,1);	///占空比
													LCD_Write_Num(28,5,PWM_Set_Duty/72,4);
													//这里需要判断正负给定并显示符号    ///显示键盘给定值
													if(setvalue < 0)
													{
															PutStr("-",5,11);
															#ifdef OPEN	
																LCD_Write_Num(72,5,(-setvalue)/36,2);	
															#else
																LCD_Write_Num(72,5,(-setvalue)/16.5,2);	
															#endif
													}	
													else
													{
															PutStr(" ",5,11);	
															LCD_Write_Num(72,5,setvalue/36,2);	
													}						
												
												  delay_ms(4000);
													if(Fun_KEY)
													{
															Fun_KEY = 0;
															LcdClearAll();
															PutHanziStr((char*)Hanzi8,1,17,2);	///返回界面
															delay_ms(4000);
															LcdClearAll();
															Boot_Menu_System();
															return;
													}
											}		
									}		
									else if(menu_Number == 2)													// 读取参数
									{
											Fun_KEY = 0;
											for(;;)
											{
													KEY_Scan(0);	
													//PutHanziStr((char*)Hanzi7,1,17,2);			///读取参数界面
													PutHanziStr((char*)Hanzi13,0,6,1);				///比例   速度 + 电流
													LCD_Write_Num(28,0,PID_Buffer[0]*100,3);
													LCD_Write_Num(62,0,PID_Buffer[3]*100,3);
												
													PutHanziStr((char*)Hanzi14,1,4,1);				///积分   速度 + 电流
													LCD_Write_Num(28,3,PID_Buffer[1]*100,3);
													LCD_Write_Num(62,3,PID_Buffer[4]*100,3);
												
													PutHanziStr((char*)Hanzi15,2,4,1);				///微分   速度 + 电流
													LCD_Write_Num(28,5,PID_Buffer[2]*100,3);	
													LCD_Write_Num(62,5,PID_Buffer[5]*100,3);												
												  delay_ms(100);
													if(Fun_KEY)
													{
															Fun_KEY = 0;
															LcdClearAll();
															PutHanziStr((char*)Hanzi8,1,17,2);		///返回界面
															delay_ms(4000);
															LcdClearAll();
															Boot_Menu_System();
															return;
													}	
											}		
									}
									else if(menu_Number == 3)
									{
											PutHanziStr((char*)Hanzi8,1,17,2);		///返回界面
											delay_ms(400);
											//delay_ms(4000);
											LcdClearAll();
											Boot_Menu_System();
											return;
									}
						}
						else if(menu_Number_Horizontal  == 1)
						{							
									if(menu_Number ==0)
									{
											Fun_KEY = 0;
											for(;;)
											{
													KEY_Scan(0);	
													PutHanziStr((char*)Hanzi2,1,15,4);	///燕山大学												
												  delay_ms(600);
													if(Fun_KEY)
													{
															Fun_KEY = 0;
															LcdClearAll();
															PutHanziStr((char*)Hanzi8,1,17,2);	///返回界面
															delay_ms(4000);
															LcdClearAll();
															Boot_Menu_System();
															return;
													}	
											}		
									}	
									else if(menu_Number == 1)
									{
											Fun_KEY = 0;
											for(;;)
											{
													KEY_Scan(0);	
													PutHanziStr((char*)Hanzi9,1,15,4);	///直流调速											
												  delay_ms(600);
													if(Fun_KEY)
													{
															Fun_KEY = 0;
															LcdClearAll();
															PutHanziStr((char*)Hanzi8,1,17,2);	///返回界面
															delay_ms(4000);
															LcdClearAll();
															Boot_Menu_System();
															return;
													}	
											}		
									}		
									else if(menu_Number == 2)
									{
											Fun_KEY = 0;
											for(;;)
											{
													KEY_Scan(0);	
													PutStr("Version 1.0 ",3,1);									
												  delay_ms(600);
													if(Fun_KEY)
													{
															Fun_KEY = 0;
															LcdClearAll();
															PutHanziStr((char*)Hanzi8,1,17,2);	///返回界面
															delay_ms(4000);
															LcdClearAll();
															Boot_Menu_System();
															return;
													}	
											}		
									
									}	
									else if(menu_Number == 3)
									{
											PutHanziStr((char*)Hanzi8,1,17,2);	///返回界面
											delay_ms(100);
											LcdClearAll();
											Boot_Menu_System();
											return;	
									}			
						}
				 }
		 }
		
}
//显示曲线
void Image_GUI(void)
{
		
}














