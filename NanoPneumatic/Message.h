// Message.h

#ifndef _MESSAGE_h
#define _MESSAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "common.h"
class MessageClass
{
public:
	String sCmd;
	String sData1;//整数部分
	String sData2;//小数部分

	bool inInt;  //状态标记 表示小数点前或后
	long cn;     //小数位数10的幂

	void init();
	void handle(int ch);
};

extern MessageClass Message;
#endif

