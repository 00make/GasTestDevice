// 
// 
// 

#include "Stepper.h"
#include <EEPROM.h>

void StepperClass::init()
{

	pinMode(DIR, OUTPUT);
	pinMode(STEP, OUTPUT);
	pinMode(ENA, OUTPUT);
	digitalWrite(DIR, HIGH);
	digitalWrite(ENA, HIGH);
	digitalWrite(STEP, LOW);

	loca lc;
	lc.d[0] = EEPROM.read(0);
	lc.d[1] = EEPROM.read(1);
	location = lc.lo;

	enable(true);
	setLocation(MAX_STEP);
}

void StepperClass::enable(bool ena)
{
	digitalWrite(ENA, !ena);
}

void StepperClass::setDir(bool dir)
{
	digitalWrite(DIR, !dir);
}

void StepperClass::runStep(long step)
{
	for (int i = 0; i < step; i++)
	{
		digitalWrite(STEP, HIGH);
		delayMicroseconds(150);
		digitalWrite(STEP, LOW);
		delayMicroseconds(250);
	}
}

void StepperClass::addLocate(long length)
{
	this->setDir(true);
	if (location + length > MAX_STEP)
	{
		this->runStep(MAX_STEP - location);
		location = MAX_STEP;
	}
	else
	{
		this->runStep(length);
		location += length;
	}

}

void StepperClass::subLocate(long length)
{
	if (length <= location)
	{
		this->setDir(false);
		runStep(length);
		location -= length;
	}
	else
	{
		this->setDir(false);
		runStep(location);
		location = 0;
	}
}

void StepperClass::setLocation(long locate)
{
	if (locate > location)
	{
		addLocate(locate - location);
		location = locate;
	}
	else
	{
		subLocate(location - locate);
		location = locate;
	}
}

void StepperClass::saveLocation()
{
	loca lc;
	lc.lo = location;
	EEPROM.write(0, lc.d[0]);
	EEPROM.write(1, lc.d[1]);

}


StepperClass Stepper;
