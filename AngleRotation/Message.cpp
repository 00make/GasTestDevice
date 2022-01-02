// 
// 
// 

#include "Message.h"
#include "Stepper.h"

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

		//处理命令
		if (sCmd.equalsIgnoreCase("ZERO"))
		{
			//回零
			Serial.println("#ZeroPos");
			Stepper.rotateToAngle(0);
			Serial.println("@OK");
		}

		if (sCmd.equalsIgnoreCase("ROTATETO"))
		{
			Serial.print("#R2:");
			Serial.println((int)p);
			Stepper.rotateToAngle((int)p);
			Serial.println("@OK");
		}
		if (sCmd.equalsIgnoreCase("CW"))
		{
			Serial.println("Set to CW");
			Stepper.setDir(true);
			Serial.println("@OK");
		}
		if (sCmd.equalsIgnoreCase("CCW"))
		{
			Serial.println("Set to CCW");
			Stepper.setDir(false);
			Serial.println("@OK");
		}
		if (sCmd.equalsIgnoreCase("ROTATE"))
		{
			Serial.print("#R:");
			Serial.println((int)p);
			Serial.print("#Current:");
			Serial.println(Stepper.currentAngle);
			Stepper.rotate((int)p);
			Serial.println("@OK");
		}
		if (sCmd.equalsIgnoreCase("ENA"))
		{
			Serial.println("#Enabled");
			Stepper.enable(true);
			Serial.println("@OK");
		}
		if (sCmd.equalsIgnoreCase("DIS"))
		{
			Serial.println("#Disabled");
			Stepper.enable(false);
			Serial.println("@OK");
		}


		this->init();
	}
}


MessageClass Message;

