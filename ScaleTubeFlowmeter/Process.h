// Process.h

#ifndef _PROCESS_h
#define _PROCESS_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include "common.h"

// S1-S4 181 205 215 159
// Ch    141 157 171 129
// Gate  150 170 184 140

#define S1_GATE 175
#define S2_GATE 195
#define S3_GATE 210
#define S4_GATE 160

#define TIMEOUT 35000

class ProcessClass
{
public:
	bool isWash;
	bool isLowSpeed;
	bool setToHigh;
	bool setToLow;

	void init();
	void prepare();
	float measure();
	void end();
};

extern ProcessClass Process;

#endif

