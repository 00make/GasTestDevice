// Menu.h

#ifndef _MENU_h
#define _MENU_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "common.h"
#include "Stepper.h"

#define MAX_MAINMENU 3

class MenuClass
{
public:

	float tempTartget;

	int sensor1State;
	int sensor2State;
	int sensorMenuIndex;//0是处于第一个传感器设置

	int mainIndex;  //1 2 3代表三项菜单
	int subIndex;  //子菜单 mainIndex*10+sub
	
	void init();

	void refreshDisplay(); //更新菜单
	void input(int key);
};

extern MenuClass Menu;

#endif

