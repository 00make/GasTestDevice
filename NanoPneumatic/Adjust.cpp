// 
// 
// 

#include "Adjust.h"
#include "Stepper.h"
#include "Sensor.h"

void AdjustClass::init()
{
	this->targetPressure = 0;
	this->motorSpeed = 0;
	this->isDoubleSensor = false;
	mPID.P = 1;
	mPID.I = 1;
	mPID.D = 1;
	vPID.P = 10;
	vPID.I = 1;
	vPID.D = 1;

	this->calValue1 = 0;
	this->calValue2 = 0;

	this->calbrate();

	this->isDisplayPInfo = false;
	this->targetReachedTag = false;
}

//修改目标气压
void AdjustClass::changeTarget(float t)
{
	targetPressure = t;
	targetReachedTag = true;
}

void AdjustClass::run()
{
	float P = readPressure();
	float e = targetPressure - P;

	if (isDisplayPInfo)
	{
		Serial.print(targetPressure);
		Serial.print("  ");
		Serial.print(P);
		Serial.print("  ");
		Serial.println(e);
	}

	if (targetReachedTag)
	{
		if (abs(e)<=0.01)
		{
			Serial.println("@Reached");
			targetReachedTag = false;
		}
	}
	
	//Serial.print("  ");
	//Serial.println(PID_P*e);
	if (e < 0)
	{
		//需减小气压
		Stepper.addLocate(abs(vPID.P*e));
		this->subMotorSpeed(abs(mPID.P*e));

	}
	else
	{
		//需加大气压
		Stepper.subLocate(abs(vPID.P*e));
		this->addMotorSpeed(abs(mPID.P*e));
	}

	static int cc = 0;
	if (cc>10)
	{
		Stepper.saveLocation();
		cc = 0;
	}
	cc++;
}

//0-180
void AdjustClass::setMotorSpeed(float s)
{
	if (s <= 0)
	{
		analogWrite(MOTOR, 0);
		motorSpeed = 0;
		return;
	}
	if (s > 180)
	{
		s = 180;
	}
	motorSpeed = s;
	analogWrite(MOTOR, (int)(motorSpeed + 75));
}

float AdjustClass::getMotorSpeed()
{
	return this->motorSpeed;
}

void AdjustClass::addMotorSpeed(float s)
{
	float tmp;
	tmp = motorSpeed + s;
	if (tmp > 180) tmp = 180;
	setMotorSpeed(tmp);
}

void AdjustClass::subMotorSpeed(float s)
{
	if (motorSpeed >= s)
	{
		setMotorSpeed(motorSpeed - s);
	}
	else
	{
		setMotorSpeed(0);
	}
}

float AdjustClass::readPressure()
{
	float r;
	if (isDoubleSensor)
	{
		float p1, p2;
		p1 = readSensorPressure(SENSORU);
		p2 = readSensorPressure(SENSORD);
		r = (p1 - calValue1) - (p2 - calValue2);
	}
	else
	{
		float p1;
		p1 = readSensorPressure(SENSORU);
		r = p1 - calValue1;
	}

	if (r<0 && r>-0.005)
	{
		r = 0;
	}
	return r;
}

float AdjustClass::readSensorPressure(int Sn)
{
	if (Sn == SENSORU)
	{
		int sum = 0;
		float p;
		for (int i = 0; i < 10; i++)
		{
			sum += analogRead(Sn);
		}
		sum = sum / 10;
		p = (Sensor.sensor1_UL - Sensor.sensor1_LL) / 4.0*(a2v(sum) - 0.5) + Sensor.sensor1_LL;
		return p;
	}
	else if (Sn == SENSORD)
	{
		int sum = 0;
		float p;
		for (int i = 0; i < 10; i++)
		{
			sum += analogRead(Sn);
		}
		sum = sum / 10;
		p = (Sensor.sensor2_UL - Sensor.sensor2_LL) / 4.0*(a2v(sum) - 0.5) + Sensor.sensor2_LL;
		return p;
	}
	else
	{
		return 0.0;
	}
}

void AdjustClass::calbrate()
{
	calValue1 = readSensorPressure(SENSORU);
	if (isDoubleSensor)
	{
		calValue2 = readSensorPressure(SENSORD);
	}

}

AdjustClass Adjust;

