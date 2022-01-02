// 
// 
// 

#include "Process.h"
#include "Message.h"

void ProcessClass::init()
{
	isWash = false;
	isLowSpeed = false;
	setToHigh = false;
	setToLow = false;

	Serial.println("#ProcessInit");
	setInner(false);
	delay(100);
	setHoseState(false);//脱离水面
	delay(1000);
	Stepper.setSlowIncrease(3, true);
	Stepper.setIncrease(7, true);//挤出管内水
	delay(500);
	Stepper.oriPos();
	Serial.println("#ProcessInit OK");
}

void ProcessClass::prepare()
{
	Serial.println("#ProcessPrepare");
	Serial.println(setToLow);
	if (setToHigh)
	{
		isLowSpeed = false;
		setToHigh = false;
		Serial.println("#High Speed Set");
	}
	if (setToLow)
	{
		isLowSpeed = true;
		setToLow = false;
		Serial.println("#Low Speed Set");
	}

	if (isLowSpeed)
	{
		setHoseState(true);
		delay(1000);
		Stepper.setSlowIncrease(0.5, false);  //吸水
		delay(500);
		setHoseState(false);
		delay(1000);
		Stepper.setSlowIncrease(2, false); //吸入   ffff

		int tmpc = 0;
		while (readSensor(S1) > S1_GATE)  //fff
		{
			Stepper.setSlowIncrease(0.05, false);
			tmpc++;
			if (tmpc > 10)
			{
				break;
			}
		}
		while (readSensor(S1) < S1_GATE)//fff
		{
			Stepper.setSlowIncrease(0.05, false);
			tmpc++;
			if (tmpc > 14)
			{
				break;
			}
		}
		Stepper.setSlowIncrease(0.25, false);
	} 
	else
	{
		setHoseState(true);
		delay(1000);
		Stepper.setSlowIncrease(0.5, false);  //吸水
		delay(500);
		setHoseState(false);
		delay(1000);
		Stepper.setSlowIncrease(1, false); //吸入   ffff

		int tmpc = 0;
		while (readSensor(S3) > S3_GATE)  //fff
		{
			Stepper.setSlowIncrease(0.05, false);
			tmpc++;
			if (tmpc > 10)
			{
				break;
			}
		}
		while (readSensor(S3) < S3_GATE)//fff
		{
			Stepper.setSlowIncrease(0.05, false);
			tmpc++;
			if (tmpc > 14)
			{
				break;
			}
		}
		Stepper.setSlowIncrease(0.2, false);
	}
	
	Serial.println("#ProcessPrepare OK");
}

float ProcessClass::measure()
{
	Serial.println("#ProcessMeasure");
	delay(1000);
	setInner(true);

	

	if (isLowSpeed)
	{
		//低流量
		Serial.println("#Low Speed Start");
		unsigned long outTime = millis();
		while (readSensor(S1) > S1_GATE)  //等待液体开始流过S1
		{
			//超时
			if (millis() - outTime > TIMEOUT * 3)
			{
				Serial.println("#Time out1");
				Serial.print("@Flowrate (mL/s):");
				Serial.println(0);
				delay(500);
				setInner(false);
				delay(500);
				Serial.println("#ProcessMeasure OK");
				return 0;
			}
		}
		outTime = millis();
		unsigned long time1;
		time1 = micros();   //记录开始时间


		while (readSensor(S2) > S2_GATE)  //S2
		{
			//超时
			if (millis() - outTime > TIMEOUT)
			{
				Serial.println("#Time out2");
				Serial.print("@Flowrate (mL/s):");
				Serial.println(0);
				delay(500);
				setInner(false);
				delay(500);
				Serial.println("#ProcessMeasure OK");
				return 0;
			}
		}
		unsigned long gap1Time = micros() - time1;

		if (gap1Time>1000000)
		{
			while (readSensor(S3) > S3_GATE)  //fff
			{
				//超时
				if (millis() - outTime > TIMEOUT * 10)
				{
					Serial.println("#Time out3");
					Serial.print("@Flowrate (mL/s):");
					Serial.println(0);
					delay(500);
					setInner(false);
					delay(500);
					Serial.println("#ProcessMeasure OK");
					return 0;
				}
			}
			unsigned long gap2Time = micros() - time1;
			Serial.print("#Gap Time S1-S3 (us):");
			Serial.println(gap2Time);

			Serial.print("@Flowrate (mL/s):");
			Serial.println(0.8 / (gap2Time / 1000000.0), 3);
		}
		else
		{
			Serial.print("#Gap Time S1-S2 (us):");
			Serial.println(gap1Time);

			Serial.print("@Flowrate (mL/s):");
			Serial.println(0.05 / (gap1Time / 1000000.0), 3);
		}
		

		
	} 
	else
	{
		Serial.println("#High Speed Start");
		//高流量 测量时间
		unsigned long outTime = millis();
		while (readSensor(S3) > S3_GATE)  //等待液体开始流过 fff
		{
			//超时
			if (millis() - outTime > TIMEOUT * 2)
			{
				Serial.println("#Time out3");
				Serial.print("@Flowrate (mL/s):");
				Serial.println(0);
				delay(500);
				setInner(false);
				delay(500);
				Serial.println("#ProcessMeasure OK");
				return 0;
			}
		}

		outTime = millis();
		unsigned long time1 = micros();

		while (readSensor(S4) > S4_GATE)  //fff
		{
			//超时
			if (millis() - outTime > TIMEOUT)
			{
				Serial.println("#Time out4");
				Serial.print("@Flowrate (mL/s):");
				Serial.println(0);
				delay(500);
				setInner(false);
				delay(500);
				Serial.println("#ProcessMeasure OK");
				return 0;
			}
		}
		unsigned long gapTime = micros() - time1;
		Serial.print("#Gap Time (us):");
		Serial.println(gapTime);

		Serial.print("@Flowrate (mL/s):");
		Serial.println(0.05 / (gapTime / 1000000.0), 3);
	}
	

	delay(1500);
	setInner(false);
	delay(500);
	Serial.println("#ProcessMeasure OK");
}

void ProcessClass::end()
{
	Serial.println("#ProcessEnd");
	if (isLowSpeed)
	{
		Stepper.setSlowIncrease(1.2, true);
	}
	if (isWash)
	{
		Stepper.setSlowIncrease(2, true);
		Stepper.setIncrease(3, true);
		delay(100);
		setHoseState(true);
		delay(400);
		Stepper.setSlowIncrease(3, false);
		delay(500);
		setHoseState(false);
		delay(500);
		Stepper.setSlowIncrease(3.2, true);
		delay(500);
		Stepper.oriPos();
		delay(500);
	} 
	else
	{
		Stepper.setSlowIncrease(1, true);//挤出剩余水
		Stepper.setIncrease(3, true);
		delay(500);
		Stepper.oriPos();
		delay(500);
	}
	Serial.println("#ProcessEnd OK");
}


ProcessClass Process;

