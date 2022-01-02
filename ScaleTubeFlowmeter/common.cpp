// 
// 
// 

#include "common.h"

Servo angleServo;
//90度水平   70朝下
int angle = 110;

void initPort()
{
	angleServo.attach(SERVO);
	setHoseState(false);
	angleServo.write(110);

	pinMode(VALVE, OUTPUT);
	digitalWrite(VALVE, HIGH);

	pinMode(LIMIT, INPUT_PULLUP);

	pinMode(EN, OUTPUT);
	pinMode(DIR, OUTPUT);
	pinMode(STEP, OUTPUT);
	digitalWrite(EN, LOW);
	digitalWrite(DIR, LOW);
}

void setHoseState(bool isInWater)
{
	if (isInWater)
	{
		if (angle == 110)
		{
			for (int i = 110; i >= 70; i--)
			{
				angleServo.write(i);
				delay(20);
			}
			angle = 70;
		}

	}
	else
	{
		if (angle == 70)
		{
			for (int i = 70; i <= 110; i++)
			{
				angleServo.write(i);
				delay(20);
			}
			angle = 110;
		}

	}
}

void setInner(bool on)
{
	if (on)
	{
		digitalWrite(VALVE, HIGH);
	}
	else
	{
		digitalWrite(VALVE, LOW);
	}
}

int readSensor(uint8_t S)
{
	int sum = 0;
	for (int i = 0; i < 10; i++)
	{
		sum += analogRead(S);
	}
	return sum / 10;
}


