// common.h

#ifndef _COMMON_h
#define _COMMON_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include <Servo.h>
#include "Stepper.h"

#define SERVO 4
#define S1 A5
#define S2 A4
#define S3 A3
#define S4 A2
#define VALVE 7
#define LIMIT 9
#define EN 8
#define STEP 2
#define DIR 5  //LOWÎü


extern Servo angleServo;

void initPort();
void setHoseState(bool isInWater);
void setInner(bool on);
int readSensor(uint8_t S);
#endif


