#include "display.h"
#include "text.h"

#define EVENTS_MODE 0
#define OFFICE_HOUR_MODE 1

char messages[10][200];
char officehours[10][200];
volatile int i = 0, e = 0, o = 0, a = 0, type = 0, char_count, offset = 0;
volatile int state = EVENTS_MODE;
volatile int waiting_for_ACK = 0;

void sendMainDisplayData(char *msg, uint8_t offset, int total)
{
	chprintf(0, 24, "%d/%d", i+1, total);
	Serial3.write(0xc);
	Serial3.write(offset);
	Serial3.write(msg);
	Serial3.write(0x17);
	waiting_for_ACK = 1;
}

void setup() {
	initializeDisplay();

	drawLogo();
	Serial.begin(57600);
	Serial1.begin(9600);
	Serial3.begin(3000);
	Serial2.begin(9600);
	Serial3.write(0xc);
	Serial3.write(0x17);
		
	int count = -1;
	while(1)
	{
		checkSerial2();
		while(Serial3.available())
		{
			Serial3.read();
			waiting_for_ACK = 0;
		}
		if(waiting_for_ACK)
		{
			while(Serial1.available())
				Serial1.read();
		}
		else if(Serial1.available())
		{
			offset = (unsigned char)Serial1.read();
			Serial.println(offset);
			/* Register swipe up and in events mode*/
			if(offset == 201 && state == EVENTS_MODE)
			{
				i = 0;
				if(o > 0)
				{
					sendMainDisplayData(officehours[i], 201, o);
				}
				chprintf(0, 16, "     ");
				elapsed_seconds = 0;
				state = OFFICE_HOUR_MODE;
				offset = 0;
				count = 0;
			}
			/* If swipe up and in office hour mode */
			else if(offset == 201 && state == OFFICE_HOUR_MODE)
			{
				chprintf(0, 16, "     ");
				elapsed_seconds = 0;
				i = 0;
				if(e > 0)
				{
					sendMainDisplayData(messages[i], 201, e);
				}
				state = EVENTS_MODE;
				offset = 0;
				count = 0;
			}
			/* If swipe left */
			else if(offset == 203)
			{
				chprintf(0, 16, "     ");
				elapsed_seconds = 0;
				if(state == EVENTS_MODE)
				{
					if(e > 0)
					{
						i = (i + 1) % e;
						sendMainDisplayData(messages[i], 203, e);
					}
					offset = 0;
					count = 0;
				}
				else if(state == OFFICE_HOUR_MODE)
				{
					i = 0;
					if(o > 0)
					{
						i = (i + 1) % o;
						sendMainDisplayData(officehours[i], 203, o);
					}
					offset = 0;
					count = 0;
				}
			}
			/* If swipe right */
			else if(offset == 202)
			{
				chprintf(0, 16, "     ");
				elapsed_seconds = 0;
				if(state == EVENTS_MODE)
				{
					if(e > 0)
					{
						i = (i-1+e)%e;
						sendMainDisplayData(messages[i], 202, e);
					}
					offset = 0;
					count = 0;
				}
				else if(state == OFFICE_HOUR_MODE)
				{
					if(o > 0)
					{
						i = (i-1+o)%o;
						sendMainDisplayData(officehours[i], 202, o);
					}
					offset = 0;
					count = 0;
				}
			}
		}
		
		chprintf(0, 16, "%d", elapsed_seconds);
		
		if(state == EVENTS_MODE)
		{
			if(elapsed_seconds >= 20)
			{
				chprintf(0, 16, "     ");
				elapsed_seconds = 0;
				if(e > 0)
				{
					i = (i+1)%e;
					sendMainDisplayData(messages[i], 203, e);
					count = 0;
					offset = 0;
				}
			}
			else if(offset != count)
			{
					sendMainDisplayData(messages[i], offset, e);
					count = offset;
			}
		}
		else if(state == OFFICE_HOUR_MODE)
		{
			if(elapsed_seconds >= 30)
			{
				chprintf(0, 16, "     ");
				elapsed_seconds = 0;
				
				if(o > 0)
				{
					i = (i+1)%o;
					sendMainDisplayData(officehours[i], 201, o);
					count = 0;
					offset = 0;
				}
				state = EVENTS_MODE;
			}
			else if(offset != count)
			{
					sendMainDisplayData(officehours[i], offset, o);
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
			Serial.print(o);
			Serial.print(" ");
			Serial.println(e);
		}
		else if(c == 0x17) 
		{
			// stop byte
			i = 0;
			type = 0;
			elapsed_seconds = 1000;
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