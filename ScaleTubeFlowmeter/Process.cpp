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
	setHoseState(false);//����ˮ��
	delay(1000);
	Stepper.setSlowIncrease(3, true);
	Stepper.setIncrease(7, true);//��������ˮ
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
		Stepper.setSlowIncrease(0.5, false);  //��ˮ
		delay(500);
		setHoseState(false);
		delay(1000);
		Stepper.setSlowIncrease(2, false); //����   ffff

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
		Stepper.setSlowIncrease(0.5, false);  //��ˮ
		delay(500);
		setHoseState(false);
		delay(1000);
		Stepper.setSlowIncrease(1, false); //����   ffff

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
		//������
		Serial.println("#Low Speed Start");
		unsigned long outTime = millis();
		while (readSensor(S1) > S1_GATE)  //�ȴ�Һ�忪ʼ����S1
		{
			//��ʱ
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
		time1 = micros();   //��¼��ʼʱ��


		while (readSensor(S2) > S2_GATE)  //S2
		{
			//��ʱ
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
				//��ʱ
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
		//������ ����ʱ��
		unsigned long outTime = millis();
		while (readSensor(S3) > S3_GATE)  //�ȴ�Һ�忪ʼ���� fff
		{
			//��ʱ
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
			//��ʱ
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
		Stepper.setSlowIncrease(1, true);//����ʣ��ˮ
		Stepper.setIncrease(3, true);
		delay(500);
		Stepper.oriPos();
		delay(500);
	}
	Serial.println("#ProcessEnd OK");
}


ProcessClass Process;

