// 
// 
// 

#include "Sensor.h"

void SensorClass::init()
{
	sensor1ListIndex = 2;
	sensor1_UL=SensorListUpper[sensor1ListIndex];
	sensor1_LL=SensorListLower[sensor1ListIndex];

	sensor2ListIndex = 0;
	sensor2_UL = SensorListUpper[sensor2ListIndex];
	sensor2_LL = SensorListLower[sensor2ListIndex];

}

void SensorClass::setSensor1Limit(int index)
{
	if (index < 0 || index>4)
	{
		return;
	}

	sensor1_UL = SensorListUpper[index];
	sensor1_LL = SensorListLower[index];

	sensor1ListIndex = index;
}

void SensorClass::setSensor2Limit(int index)
{
	if (index < 0 || index>4)
	{
		return;
	}

	sensor2_UL = SensorListUpper[index];
	sensor2_LL = SensorListLower[index];

	sensor2ListIndex = index;
}


SensorClass Sensor;

