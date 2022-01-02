// Sensor.h

#ifndef _SENSOR_h
#define _SENSOR_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class SensorClass
{
public:
	const int SensorListUpper[5] = { 1,2,5,40,300 };
	const int SensorListLower[5] = { -1,-2,-5,-40,-100 };

	int sensor1_UL;
	int sensor1_LL;
	int sensor1ListIndex;

	int sensor2_UL;
	int sensor2_LL;
	int sensor2ListIndex;

	void init();
	void setSensor1Limit(int index);
	void setSensor2Limit(int index);
};

extern SensorClass Sensor;

#endif

