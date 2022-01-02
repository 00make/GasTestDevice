/*
 Name:		AngleRotation.ino
 Created:	2019/5/12/周日 15:00:42
 Author:	HP
*/
#include "Stepper.h"
#include "Message.h"


// the setup function runs once when you press reset or power the board
void setup() 
{
	Serial.begin(57600);
	Stepper.init();
	Message.init();
	Stepper.enable(false);
	Serial.println("@RotateAng");
}

// the loop function runs over and over again until power down or reset
void loop() 
{
	while (Serial.available() > 0)
	{
		Message.handle(Serial.read());
	}
}
