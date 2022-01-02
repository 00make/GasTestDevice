// 
// 
// 

#include "common.h"

Adafruit_PCD8544 display = Adafruit_PCD8544(8, 9, 10, 11, 12);




void initGPIO()
{
	pinMode(KEYC, INPUT_PULLUP);
	pinMode(KEYL, INPUT_PULLUP);
	pinMode(KEYR, INPUT_PULLUP);

	analogWrite(MOTOR, 0);
}

void initWait()
{
	for (int i = 10; i--; i >= 0)
	{
		display.setContrast(54);
		display.clearDisplay();
		display.setCursor(16, 10);
		display.println("Regulated");
		display.setCursor(14, 19);
		display.println("Air Supply");
		display.setCursor(36, 30);
		display.print(i);
		display.display(); // show splashscreen
		delay(990);

		if (scanKey(KEYC))
		{
			break;
		}
	}

}

float a2v(int a)
{
	return a / 1024.0 * 5;
}



bool scanKey(uint8_t key)
{
	if (!digitalRead(key))
	{
		while (!digitalRead(key))
		{
		}
		return true;
	}
	else
	{
		return false;
	}
}
int scanAllKey()
{
	if (scanKey(KEYC))
	{
		return KEYC;
	}
	if (scanKey(KEYL))
	{
		return KEYL;
	}
	if (scanKey(KEYR))
	{
		return KEYR;
	}
	return 0;
}