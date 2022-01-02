// Measure.h

#ifndef _MEASURE_h
#define _MEASURE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class MeasureClass
{
protected:


public:
	void init();
	void run();
};

extern MeasureClass Measure;

#endif

