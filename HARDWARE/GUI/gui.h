#ifndef __GUI_H__
#define __GUI_H__

#include "stm32f10x.h"
#include "timer.h"

#include "KEY.h"


//��ʾϵͳ�˵�
void SystemMenu_GUI(void);
void SystemSonMenu(void);
void SystemMenu(void);
void Boot_Menu(void);
void Boot_Menu_System(void);
void Boot_Menu_Image(void);
void Boot_Menu_Music(void);
void Menu_Select(void);
//��ʾ����
void Image_GUI(void);
//��ʾ����
//void Seting_GUI(void);

extern int menu_Number;
void menu_Select(void);

#endif
