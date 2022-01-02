// 
// 
// 

#include "Message.h"
#include "Process.h"

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
		if (sCmd.equalsIgnoreCase("PREPARE"))
		{
			if (!isAutoMode)
			{
				Process.prepare();
				currentOp = 1;
			}
			else
			{
				Serial.println("#Auto Mode!");
			}
		}

		if (sCmd.equalsIgnoreCase("MEASURE"))
		{
			if (!isAutoMode)
			{
				Process.measure();
				currentOp = 2;
			}
			else
			{
				Serial.println("#Auto Mode!");
			}
		}

		if (sCmd.equalsIgnoreCase("ENDOP"))
		{
			if (!isAutoMode)
			{
				Process.end();
				currentOp = 3;
			}
			else
			{
				Serial.println("#Auto Mode!");
			}
		}

		if (sCmd.equalsIgnoreCase("INIT"))
		{
			if (!isAutoMode)
			{
				Process.init();
				currentOp = 0;
			}
			else
			{
				Serial.println("#Auto Mode!");
			}
		}

		if (sCmd.equalsIgnoreCase("GETDATA"))
		{
			if (isAutoMode)
			{
				startMeasure = true;
			}
			else
			{
				Serial.println("#Manual Mode!");
			}
		}

		if (sCmd.equalsIgnoreCase("AUTO"))
		{
			isAutoMode = true;
			Serial.println("#Auto Mode");
			Serial.println("@OK");
		}

		if (sCmd.equalsIgnoreCase("MANUAL"))
		{
			isAutoMode = false;
			Serial.println("#Manual Mode");
			Serial.println("@OK");
		}

		if (sCmd.equalsIgnoreCase("HIGHSPEED"))
		{
			Process.setToHigh = true;
			Serial.println("#Setting High Speed Mode");
		}

		if (sCmd.equalsIgnoreCase("LOWSPEED"))
		{
			Process.setToLow = true;
			Serial.println("#Setting Low Speed Mode");
		}

		if (sCmd.equalsIgnoreCase("WASH"))
		{
			//每次测完都洗内壁   end操作里面加
			Process.isWash = true;
			Serial.println("#Wash Mode On");
		}

		if (sCmd.equalsIgnoreCase("NOWASH"))
		{
			//取消洗
			Process.isWash = false;
			Serial.println("#Wash Mode Off");
		}

		this->init();
	}
}


MessageClass Message;

