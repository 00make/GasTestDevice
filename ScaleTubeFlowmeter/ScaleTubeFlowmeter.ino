/*
Name:		ScaleTubeFlowmeter.ino
Created:	2019/5/8/周三 23:36:25
Author:	HP
*/

#include "Stepper.h"
#include "Process.h"
#include "Measure.h"
#include "common.h"
#include "Message.h"
#include "Process.h"
#include "Stepper.h"
#include <Servo.h>

void setup()
{
	initPort();
	Serial.begin(57600);
	Serial.println("@ScaleTubeFlowmeter");
	Stepper.init();
	Message.init();

	setInner(false);
	setHoseState(false);//脱离水面
	Serial.println("#Please Open ExtPower");
	delay(500);
	
	Process.init();
	delay(1000);
	Serial.println("@Start");
}


void loop()
{
	while (Serial.available() > 0)
	{
		Message.handle(Serial.read());
	}

	if (Message.isAutoMode)
	{
		switch (Message.currentOp)
		{
		case 0:
			Process.prepare();
			Message.currentOp = 1;
			Serial.println("@Ready");
			break;
		case 1:
			if (Message.startMeasure)
			{
				Process.measure();
				Message.currentOp = 2;
				Message.startMeasure = false;
			}
			break;
		case 2:
			Process.end();
			Message.currentOp = 3;
			break;
		case 3:
			Process.prepare();
			Message.currentOp = 1;
			Serial.println("@Ready");
			break;
		default:
			break;
		}
	}



	//delay(100);
}
