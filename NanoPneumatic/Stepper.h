// Stepper.h

#ifndef _STEPPER_h
#define _STEPPER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "common.h"

#define MAX_STEP 1500

union loca
{
	int lo;
	byte d[2];
};

class StepperClass
{
public:
	long location;
	void init();
	void enable(bool ena);
	void setDir(bool dir);
	void runStep(long step);

	void addLocate(long length);
	void subLocate(long length);
	void setLocation(long locate);

	void saveLocation();
};

extern StepperClass Stepper;

#endif


