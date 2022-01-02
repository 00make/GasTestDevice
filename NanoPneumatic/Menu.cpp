// 
// 
// 

#include "Menu.h"
#include "Adjust.h"
#include "Sensor.h"

const char sensorStr[5][6] = {
	"@1",
	"@2",
	"@5",
	"@40",
	"@300"
};


void MenuClass::init()
{
	mainIndex = 1;
	subIndex = 0;

	tempTartget = Adjust.targetPressure;

	sensor1State = Sensor.sensor1ListIndex;
	sensor2State = -1;
	sensorMenuIndex = 0;
}

void MenuClass::refreshDisplay()
{
	display.clearDisplay();

	display.setCursor(0, 3);
	display.print("PV:");
	display.print(Adjust.readPressure(), 1);
	display.setCursor(42, 3);
	display.print("SV:");
	display.println(Adjust.targetPressure, 1);
	display.drawRect(0, 0, 84, 2, 0xFFFF);
	display.drawRect(0, 11, 84, 2, 0xFFFF);

	display.setCursor(5, 14);
	display.print("V:");
	display.print((int)(Stepper.location / (float)MAX_STEP * 100));
	display.print("%");
	display.setCursor(45, 14);
	display.print("M:");
	display.print((int)(Adjust.getMotorSpeed() / 180.0 * 100));
	display.println("%");

	if (mainIndex == 0)
	{
		display.display();
		return;
	}

	display.drawRoundRect(0, 22, 84, 26, 3, 0xFFFF);
	display.setCursor(8, 24);
	display.print("SET");
	display.setCursor(8, 32);
	display.print("SNN");
	display.setCursor(8, 40);
	display.print("CAL");

	display.setCursor(2, 16 + mainIndex * 8);
	display.print(">");

	//打开了子菜单
	if (subIndex)
	{
		switch (mainIndex)
		{
		case 1:
			//设置目标值
			display.setCursor(30, 24);
			display.print(">>");
			display.print(tempTartget, 1);
			break;
		case 2:
			display.setCursor(30, 32);
			if (!sensorMenuIndex)
			{
				//第一个传感器
				display.print("S1:");
				display.print(sensorStr[sensor1State]);
			}
			else
			{
				display.print("S2:");
				if (sensor2State==-1)
				{
					display.print("None");
				}
				else
				{
					display.print(sensorStr[sensor2State]);
				}
			}
			break;
		case 3:
			display.setCursor(30, 40);
			display.print("OK?");
			break;
		default:
			break;
		}
	}


	display.display();
}

void MenuClass::input(int key)
{
	if (subIndex)
	{
		//进入了子菜单  设置项
		switch (mainIndex)
		{
		case 1:
			//调节压力
			switch (key)
			{
			case KEYL:
				tempTartget -= 0.1;
				break;
			case KEYR:
				tempTartget += 0.1;
				break;
			case KEYC:
				Adjust.changeTarget(tempTartget);
				subIndex = 0;
				break;
			default:
				break;
			}
			break;
		case 2:
			//设置传感器数量
			switch (key)
			{
			case KEYL:
				if (!sensorMenuIndex)
				{
					sensor1State--;
					if (sensor1State<0)
					{
						sensor1State = 4;
					}
				} 
				else
				{
					sensor2State--;
					if (sensor2State < -1)
					{
						sensor2State = 4;
					}
				}
				break;
			case KEYR:
				if (!sensorMenuIndex)
				{
					sensor1State++;
					if (sensor1State>4)
					{
						sensor1State = 0;
					}
				}
				else
				{
					sensor2State++;
					if (sensor2State>4)
					{
						sensor2State = -1;
					}
				}
				break;
			case KEYC:
				if (sensorMenuIndex==0)
				{
					sensorMenuIndex = 1;
				}
				else
				{
					//处理sensorState到isDoubleSensor和量程
					Sensor.setSensor1Limit(sensor1State);
					if (sensor2State==-1)
					{
						Adjust.isDoubleSensor = false;
					} 
					else
					{
						Adjust.isDoubleSensor = true;
						Sensor.setSensor2Limit(sensor2State);
					}
					
					Adjust.calbrate();
					subIndex = 0;
					sensorMenuIndex = 0;
				}
				
				break;
			default:
				break;
			}
			break;
		case 3:
			//校准
			switch (key)
			{
			case KEYL:
				subIndex = 0;
				break;
			case KEYR:
				subIndex = 0;
				break;
			case KEYC:
				Adjust.calbrate();
				subIndex = 0;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}
	else
	{
		//调整菜单
		switch (key)
		{
		case KEYR:
			mainIndex++;
			if (mainIndex > MAX_MAINMENU)
			{
				mainIndex = 1;
			}
			break;
		case KEYL:
			mainIndex--;
			if (mainIndex == 0)
			{
				mainIndex = 3;
			}
			break;
		case KEYC:
			subIndex = 1;
			break;
		default:
			break;
		}
	}
}



MenuClass Menu;

