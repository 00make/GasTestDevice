// 
// 
// 

#include "Message.h"
#include "Stepper.h"
#include "Adjust.h"

void MessageClass::init()
{
	sCmd = "";
	sData1 = "";
	sData2 = "";
	inInt = true;
	cn = 1;
}

void MessageClass::handle(int ch)
{
	float p;
	int inChar = ch;
	if (isDigit(inChar))
	{
		if (inInt)
		{
			sData1 += (char)inChar;
		}
		else
		{
			sData2 += (char)inChar;
			cn *= 10;
		}
	}
	if (inChar == '.')
	{
		inInt = false;
	}
	if (isAlpha(inChar))
	{
		sCmd += (char)inChar;
	}
	if (inChar == '\n')
	{
		if (inInt) p = sData1.toInt();
		else p = sData1.toInt() + (float)sData2.toInt() / cn;

		//´¦ÀíÃüÁî
		if (sCmd.equalsIgnoreCase("SETTARGET"))
		{
			if (p >= 0 && p < 100)
			{
				Adjust.changeTarget(p);
				Serial.print("#Change target:");
				Serial.println(p);
			}
			else
			{
				Serial.print("#Change target failed:");
				Serial.println(p);
			}
		}

		if (sCmd.equalsIgnoreCase("GETTARGET"))
		{
			Serial.print("#Current target:");
			Serial.println(p);
		}

		if (sCmd.equalsIgnoreCase("STARTSTEP"))
		{
			Stepper.enable(true);
			Serial.println("#Start stepper");
		}

		if (sCmd.equalsIgnoreCase("STOPSTEP"))
		{
			Stepper.enable(false);
			Serial.println("#Stop stepper");
		}


		this->init();
	}
}


MessageClass Message;

