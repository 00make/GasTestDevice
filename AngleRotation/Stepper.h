// Stepper.h

#ifndef _STEPPER_h
#define _STEPPER_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define CW 1
#define CCW 0

#define EN 8
#define X_SETP 2
#define Y_SETP 3
#define Z_SETP 4
#define X_DIR 5
#define Y_DIR 6
#define Z_DIR 7

class StepperClass
{
	
public:
	int currentStep;
	bool isCW;
	int currentAngle;


	void init();
	void setDir(bool isCW);
	void enable(bool en);
	void oneStep();
	void rotateToAngle(int ang);
	void rotate1();
	void rotate(int a);
};

extern StepperClass Stepper;

#endif

