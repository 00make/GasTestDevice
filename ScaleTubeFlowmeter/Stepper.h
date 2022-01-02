// Stepper.h

#ifndef _STEPPER_h
#define _STEPPER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "common.h"

#define PLUSEPERCC 278.0

class StepperClass
{
protected:


public:
	void init();
	void setDir(bool isPush);
	void oneStep();
	void slowStep();
	void runStep(int n);
	void runSlowStep(int n);
	void setIncrease(float volcc, bool dirPush);
	void setSlowIncrease(float volcc, bool dirPush);
	void zeroPos();
	void oriPos();
};

extern StepperClass Stepper;

#endif

