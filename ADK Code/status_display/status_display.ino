#include "display.h"
#include "text.h"

volatile char messages[10][200];
volatile char officehours[10][200];
volatile int e = 0, o = 0, a = 0, type = 0, char_count, offset = 0;

void setup() {
	initializeDisplay();

	drawLogo();
	Serial.begin(2400);
	Serial1.begin(57600);
	Serial3.begin(2400);
	Serial2.begin(2400);
	Serial3.write(0xc);
	Serial3.write(0x17);
		
	int i = 0;
	int count = -1;
	while(1)
	{
		checkSerial2();
		if(Serial1.available())
		{
			offset = Serial1.read();
			if(offset == 201)
			{
				
			}
			else if(offset == 202)
			{
				// Serial3.write(0xc);
				// char zero = 0;
				// Serial3.write(zero);
				// Serial3.write(LEFT);
				// Serial3.write((char *)messages[++i]);
				// Serial3.write(0x17);
				// i++;
			}
		}
			
		writeChar(0, 16, (char)(elapsed_seconds+'0'), WHITE);
		if(i >= e)
		{
			i = 0;
			// if(i == e)
			// {
				// writeChar(0, 24, 'O', WHITE);
				// Serial3.write(0xc);
				// Serial3.write(elapsed_seconds);
				// Serial3.write("Office Hours");
				// Serial3.write(0x17);
			// }
			// i = i + elapsed_seconds;
			// if(i == e + 10)
				// i = 0;
		}
		else
		{
			if(elapsed_seconds >= 10)
			{
				elapsed_seconds = 0;
				if(e > 0)
				{
					writeChar(0, 24, (char)(i+48), WHITE);
					Serial3.write(0xc);
					char zero = 0;
					Serial3.write(zero);
					Serial3.write(LEFT);
					Serial3.write((char *)messages[i]);
					Serial3.write(0x17);
					i++;
				}
			}
			else if(offset != count)
			{
					writeChar(0, 24, (char)(i+48), WHITE);
					Serial3.write(0xc);
					Serial3.write(offset);
					Serial3.write((char *)messages[i]);
					Serial3.write(0x17);
					count = offset;
			}
		}
	}
}

void checkSerial2()
{
	char c;
	while (Serial2.available())
	{
		c = Serial2.read();
		if (c == -1)
		{
			// error, do nothing
		}
		else if (c == 'O' && !type)
		{
			// start byte
			type = c;
			char_count = 0;
			o = 0;
		}
		else if (c == 'E' && !type)
		{
			// start byte
			type = c;
			e = 0;
			char_count = 0;
		}
		else if(c == 0)
		{
			if(type == 'E')
			{
				messages[e++][char_count++] = 0;
				char_count = 0;
			}
			else if(type == 'O')
			{
				officehours[o++][char_count++] = 0;
				char_count = 0;
			}
			
		}
		else if(c == 0x17) 
		{
			// stop byte
			if(type == 'E')
			{
				messages[e++][char_count++] = 0;
				char_count = 0;
			}
			else if(type == 'O')
			{
				officehours[o++][char_count++] = 0;
				char_count = 0;
			}
			type = 0;
			break;
		}
		else
		{
			Serial.print(c);
			if(type == 'E')
				messages[e][char_count++] = c;
			else if(type == 'O')
				officehours[o][char_count++] = c;	
		}
	}
}

// will never enter this function, but must be defined
// we just do everyting in setup()
void loop() {}