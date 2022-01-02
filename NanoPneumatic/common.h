// common.h

#ifndef _COMMON_h
#define _COMMON_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define MOTOR 3
#define DIR 4
#define STEP 5
#define ENA 6
#define CLK 8
#define DIN 9
#define DC 10
#define CE 11
#define RST 12

#define KEYL A2
#define KEYC A1
#define KEYR A0

#define SENSORU A5
#define SENSORD A4





extern Adafruit_PCD8544 display;


void initGPIO();
void initWait();


float a2v(int a);

bool scanKey(uint8_t key);
int scanAllKey();

#endif

