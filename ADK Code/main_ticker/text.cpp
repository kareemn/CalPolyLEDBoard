#include "text.h"
#include <arduino.h>

int test = -1;

void writeChar(int x, int y, char c, Color color)
{
	for (int i=0; i<6; i++ ) {
		if (test < 0 || x+i == test)
		{
			int line;
			if (i == 5) 
				line = 0x0;
			else 
				line = font[((c-32)*5)+i];
			
			for (int j = 0; j<8; j++) {
				if (line & 0x1) 
				{
					setPixel(x+i, y+j, color);
				}
				else
				{
					setPixel(x+i, y+j, BLACK);
				}
				line >>= 1;
			}
		}
	}
}

void writeDisplay(int x, int y, char *str)
{
	Color color = WHITE;
	char c;
	int a = x;
	int b = y;
	
	while ((c = *(str++)))
	{
		if (c <= WHITE)
		{
			color = c;
		}
		else if (c == '\n')
		{
			a = x;
			b += 10;
		}
		else
		{
			writeChar(a, b, c, color);
			a += 6;
		}
	}
}

// void transitionUp(int x, int y, char *str)
// {
	// Color color = WHITE;
	// char c;
	// int offset = 0;
	// int a = x;
	// int b = y;
	
	// for(int i = 0; i<16; i++)
	// {
		// clearDisplay();
		// offset += 2;
		// char *temp = str;
		// while ((c = *(temp++)))
		// {
			// if (c <= WHITE)
			// {
				// color = c;
			// }
			// else if (c == '\n')
			// {
				// a = 1;
				// b += 10;
			// }
			// else
			// {
				// writeChar(a, b-offset, c, color);
				// a += 6;
			// }
		// }
		// delay(10);
	// }
// }

void transitionRight(int x, int y, char *str)
{
	clearDisplay();
	writeDisplay(x, y, str);
	test = 0;
	
	int offset = 0;
	for(int i = 0; i<320; i++)
	{
		offset++;
		writeDisplay(x+offset, y, str);
		shiftDisplayRight();
		delay(1);
	}
	test = -1;
}

void transitionLeft(int x, int y, char *str)
{
	clearDisplay();
	writeDisplay(x, y, str);
	test = 319;
	
	int offset = 0;
	for(int i = 0; i<320; i++)
	{
		offset--;
		writeDisplay(x+offset, y, str);
		shiftDisplayLeft();
		delay(1);
	}
	test = -1;
}

void transitionUp(int x, int y, char *str)
{
	for(int i = 0; i<32; i++)
	{
		clearDisplay();
		writeDisplay(x, y-i, str);
		delay(10);
	}
}