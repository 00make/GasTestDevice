// Message.h

#ifndef _MESSAGE_h
#define _MESSAGE_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class MessageClass
{
public:
	String sCmd;
	String sData1;//��������
	String sData2;//С������

	bool inInt;  //״̬��� ��ʾС����ǰ���
	long cn;     //С��λ��10����

	void init();
	void handle(int ch);
};

extern MessageClass Message;
#endif

