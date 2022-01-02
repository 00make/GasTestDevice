// Adjust.h

#ifndef _ADJUST_h
#define _ADJUST_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "common.h"

#define MOTOR_ADJUST_THRESHOLD 3

class AdjustClass
{
private:
	struct PID
	{
		float P;
		float I;
		float D;
	};
	PID mPID;
	PID vPID;

public:
	float motorSpeed;

	float targetPressure;
	bool isDoubleSensor;

	float calValue1, calValue2;

	bool isDisplayPInfo;
	bool targetReachedTag;

	void init();
	void changeTarget(float t);
	void run();

	void setMotorSpeed(float s);
	float getMotorSpeed();
	void addMotorSpeed(float s);
	void subMotorSpeed(float s);

	float readPressure();
	float readSensorPressure(int Sn);
	void calbrate();
};

extern AdjustClass Adjust;

#endif

