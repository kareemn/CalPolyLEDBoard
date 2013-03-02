#include "display.h"
#include "text.h"

volatile char events[10][200];
volatile char officehours[10][200];
volatile char announcements[10][200];
volatile char FAQ[10][200];
volatile int e = 0, o = 0, a = 0, f = 0, type = 0, char_count;

void setup() {
	initializeDisplay();

	drawLogo();
	Serial.begin(2400);
	Serial3.begin(2400);
	Serial2.begin(2400);
	Serial3.write(0xc);
	Serial3.write(0x17);
	
	// char *strings[8];
	// strings[0] = "Hi there!";
	// strings[1] = "How's it going?";
	// strings[2] = "Hope all is well";
	// strings[3] = "Would you like to hear a joke?";
	// strings[4] = "Why did everyone love the mushroom?";
	// strings[5] = "...";
	// strings[6] = "Because he was a fun-gi.";
	// strings[7] = "Hahahah, I'm funny.";
		
	int i = 0;
	int count = -1;
	while(1)
	{
		checkSerial2();
		writeChar(0, 16, (char)(elapsed_seconds+'0'), WHITE);
		if(elapsed_seconds >= 10)
		{
			elapsed_seconds = 0;
			if(e > 0)
			{
				writeChar(0, 24, 'E', WHITE);
				writeChar(6, 24, (char)(i+48), WHITE);
				Serial3.write(0xc);
				char zero = 0;
				Serial3.write(zero);
				Serial3.write((char *)events[i]);
				Serial3.write(0x17);
				i++;
			}
		}
		else if(elapsed_seconds != count)
		{
				writeChar(0, 24, 'E', WHITE);
				writeChar(6, 24, (char)(i+48), WHITE);
				Serial3.write(0xc);
				Serial3.write(elapsed_seconds);
				Serial3.write((char *)events[i]);
				Serial3.write(0x17);
				count = elapsed_seconds;
		}
		if(i == e)
			i = 0;
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
				events[e++][char_count++] = 0;
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
				events[e++][char_count++] = 0;
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
				events[e][char_count++] = c;
			else if(type == 'O')
				officehours[o][char_count++] = c;	
		}
	}
}

// will never enter this function, but must be defined
// we just do everyting in setup()
void loop() {}