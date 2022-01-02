// 
// 
// 

#include "Stepper.h"

void StepperClass::init()
{
	for (int i = 2; i < 8; i++)
	{
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
	}
	currentStep = 0;
	currentAngle = 0;
	isCW = 0;
	enable(false);
}

void StepperClass::setDir(bool isCW)
{
	digitalWrite(X_DIR, isCW);
	this->isCW = isCW;
}

void StepperClass::enable(bool en)
{
	digitalWrite(EN, !en);
}

void StepperClass::oneStep()
{
	digitalWrite(X_SETP, HIGH);
	delayMicroseconds(200);
	digitalWrite(X_SETP, LOW);
	delay(4);
}

void StepperClass::rotateToAngle(int ang)
{
	if (ang < 0 || ang>359)
	{
		return;
	}
	int t = ang*3200.0 / 360;
	if (isCW)
	{
		//顺时针
		while (currentStep != t)
		{
			oneStep();
			currentStep--;
			if (currentStep<0)
			{
				currentStep = 3199;
			}
		}

	} 
	else
	{
		//逆时针
		while (currentStep != t)
		{
			oneStep();
			currentStep++;
			if (currentStep>3199)
			{
				currentStep = 0;
			}
		}
	}
	currentAngle = ang;
}

void StepperClass::rotate(int a)
{
	for (int i= 0; i < a; i++)
	{
		rotate1();
	}
}

void StepperClass::rotate1()
{
	if (isCW)
	{
		if (currentAngle==0)
		{
			rotateToAngle(359);
		}
		else
		{
			rotateToAngle(currentAngle - 1);
		}
	} 
	else
	{
		if (currentAngle==359)
		{
			rotateToAngle(0);
		} 
		else
		{
			rotateToAngle(currentAngle + 1);
		}
		
	}
}



StepperClass Stepper;

