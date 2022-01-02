/*
Name:		NanoPneumatic.ino
Created:	2019/5/5/周日 15:14:10
Author:	HP

Timer2用于产生周期的中断  检测按键
Timer1用于驱动步进电机
*/

#include "Sensor.h"
#include <EEPROM.h>
#include "Adjust.h"
#include "Message.h"
#include "Stepper.h"
#include "Menu.h"
#include "common.h"
#include "Adjust.h"
#include "Message.h"
#include "Menu.h"
#include <TimerOne.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "Stepper.h"
#include "common.h"

void setup()
{
	Serial.begin(57600);
	Serial.println("@RegulatedAirSupply");
	initGPIO();

	display.begin();
	initWait();
	Sensor.init();
	Menu.init();
	Adjust.init();
	Stepper.init();
	Message.init();
	Timer1.initialize(50000);
	Timer1.attachInterrupt(task);
}

void loop()
{
	while (Serial.available() > 0)
	{
		Message.handle(Serial.read());
	}
	Menu.refreshDisplay();
	Menu.input(scanAllKey());
	delay(2);
}

void task()
{
	Adjust.run();
}
