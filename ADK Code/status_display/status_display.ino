#include "display.h"
#include "text.h"

#define EVENTS_MODE 0
#define OFFICE_HOUR_MODE 1

char messages[10][200];
char officehours[10][200];
volatile int e = 0, o = 0, a = 0, type = 0, char_count, offset = 0;
volatile int state = EVENTS_MODE;

void setup() {
	initializeDisplay();

	drawLogo();
	Serial.begin(57600);
	Serial1.begin(57600);
	Serial3.begin(3000);
	Serial2.begin(2400);
	Serial3.write(0xc);
	Serial3.write(0x17);
		
	strcpy(officehours[0], "Lupo, in the CS offices, sometime during the week");
	o++;
		
	int i = 0;
	int count = -1;
	while(1)
	{
		checkSerial2();
		if(Serial1.available())
		{
			offset = (unsigned char)Serial1.read();
			Serial.println(offset);
			/* Register swipe up and in events mode*/
			if(offset == 201 && state == EVENTS_MODE)
			{
				i = 0;
				if(o > 0)
				{
					Serial3.write(0xc);
					Serial3.write(offset);
					Serial3.write((char *)officehours[i++]);
					Serial3.write(0x17);
				}
				elapsed_seconds = 0;
				state = OFFICE_HOUR_MODE;
				offset = 0;
				count = 0;
			}
			/* If swipe up and in office hour mode */
			else if(offset == 201 && state == OFFICE_HOUR_MODE)
			{
				elapsed_seconds = 0;
				i = 0;
				if(o > 0)
				{
					Serial3.write(0xc);
					Serial3.write(201);
					Serial3.write(1);
					Serial3.write((char *)messages[i++]);
					Serial3.write(0x17);
				}
				state = EVENTS_MODE;
				offset = 0;
				count = 0;
			}
			/* If swipe left */
			else if(offset == 203)
			{
				elapsed_seconds = 0;
				if(state == EVENTS_MODE)
				{
					if(i >= e)
						i = 0;
					if(e > 0)
					{
						Serial3.write(0xc);
						Serial3.write(203);
						Serial3.write((char *)messages[i++]);
						Serial3.write(0x17);
					}
					offset = 0;
					count = 0;
				}
			}
			/* If swipe right */
			else if(offset == 202)
			{
				elapsed_seconds = 0;
				if(state == EVENTS_MODE)
				{
					if(i < 0)
						i = e-1;
					if(e > 0)
					{
						Serial3.write(0xc);
						Serial3.write(202);
						Serial3.write((char *)messages[i--]);
						Serial3.write(0x17);
					}
					offset = 0;
					count = 0;
				}
				else if(state == OFFICE_HOUR_MODE)
				{
					i = 0;
					if(o > 0)
					{
						Serial3.write(0xc);
						Serial3.write(offset);
						Serial3.write((char *)officehours[i++]);
						Serial3.write(0x17);
					}
					offset = 0;
					count = 0;
				}
			}
		}
		
		writeChar(0, 16, (char)(elapsed_seconds+'0'), WHITE);
		
		if(state == EVENTS_MODE)
		{
			if(i >= e)
				i = 0;

			if(elapsed_seconds >= 10)
			{
				elapsed_seconds = 0;
				if(e > 0)
				{
					writeChar(0, 24, (char)(i+48), WHITE);
					Serial3.write(0xc);
					Serial3.write(203);
					Serial3.write((char *)messages[i]);
					Serial3.write(0x17);
					i++;
					count = 0;
					offset = 0;
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
		else if(state == OFFICE_HOUR_MODE)
		{
			if(i >= o)
				i = 0;
				
			if(elapsed_seconds >= 30)
			{
				elapsed_seconds = 0;
				if(i >= e)
					i = 0;
				if(o > 0)
				{
					writeChar(0, 24, (char)(i+48), WHITE);
					Serial3.write(0xc);
					char zero = 0;
					Serial3.write(zero);
					Serial3.write((char *)officehours[i++]);
					Serial3.write(0x17);
					i++;
					count = 0;
					offset = 0;
				}
				state = EVENTS_MODE;
			}
			else if(offset != count)
			{
					writeChar(0, 24, (char)(i+48), WHITE);
					Serial3.write(0xc);
					Serial3.write(offset);
					Serial3.write((char *)officehours[i]);
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
			Serial.print(" ");
			Serial.println(e);
		}
		else if(c == 0x17) 
		{
			// stop byte
			type = 0;
			Serial.println(e);
			Serial.println(o);
		}
		else
		{
			//Serial.print(c);
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