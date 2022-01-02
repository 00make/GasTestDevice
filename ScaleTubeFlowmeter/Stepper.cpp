// 
// 
// 

#include "Stepper.h"

void StepperClass::init()
{
	digitalWrite(EN, LOW);

}

void StepperClass::setDir(bool isPush)
{
	digitalWrite(DIR, isPush);
}

void StepperClass::oneStep()
{
	digitalWrite(STEP, HIGH);
	delayMicroseconds(250);
	digitalWrite(STEP, LOW);
	delayMicroseconds(500);
}

void StepperClass::slowStep()
{
	digitalWrite(STEP, HIGH);
	delay(5);
	digitalWrite(STEP, LOW);
	delay(5);
}

void StepperClass::runStep(int n)
{
	for (int i = 0; i < n; i++)
	{
		oneStep();
	}
}

void StepperClass::runSlowStep(int n)
{
	for (int i = 0; i < n; i++)
	{
		slowStep();
	}
}

void StepperClass::setIncrease(float volcc, bool dirPush)
{
	setDir(dirPush);
	runStep(PLUSEPERCC * volcc);
}

void StepperClass::setSlowIncrease(float volcc, bool dirPush)
{
	setDir(dirPush);
	runSlowStep(PLUSEPERCC * volcc);
}

void StepperClass::zeroPos()
{
	setDir(false);
	while (!digitalRead(LIMIT))
	{
		oneStep();
	}
	setDir(true);
	runStep(200);
	setDir(false);
	while (!digitalRead(LIMIT))
	{
		oneStep();
		delay(3);
	}
	setDir(true);
	setIncrease(1.7, true);
}

void StepperClass::oriPos()
{
	Stepper.zeroPos();  //回零
	Stepper.setIncrease(5, true); //回原位
}


StepperClass Stepper;

