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

// void writeDisplay2(char *str, int x_offset)
// {
	// Color color = WHITE;
	// char c;
	// int x=1, y=2;
	// while ((c = *(str++)))
	// {
		// if (c <= WHITE)
		// {
			// color = c;
		// }
		// else if (c == '\n')
		// {
			// x = 1;
			// y += 10;
		// }
		// else
		// {
			// writeChar(x-x_offset, y, c, color);
			// x += 6;
		// }
	// }
// }

// void writeString(TextRow row, char *str)
// {
	// Color color = WHITE;
	// char c;
	// int x = 1;
	// int y = 2 + (row * 10);
	// while ((c = *(str++)))
	// {
		// if (c <= WHITE)
		// {
			// color = c;
		// }
		// else
		// {
			// writeChar(x, y, c, color);
			// x += 6;
		// }
	// }
// }

volatile Color display2[1800][8];

void writeChar2(int x, int y, unsigned char c, Color color)
{
	for (int i=0; i<6; i++ ) {
		int line;
		if (i == 5) 
			line = 0x0;
		else
			line = font[((c-32)*5)+i];
		
		for (int j = 0; j<8; j++) {
			if (line & 0x1) 
			{
				display2[x+i][y+j] = color;
			}
			else
			{
				display2[x+i][y+j] = 0;
			}
			line >>= 1;
		}
	}
}

int writeScrollingText(unsigned char *str, Color text)
{
	// clear second display buffer
	for (int i = 0; i < 1800; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			display2[i][j] = 0;
		}
	}

	unsigned char c;
	int x = 0;
	while ((c = *(str++)))
	{
		writeChar2(x, 0, c, text);
		x += 6;
		if (x >= 1800)
		{
			x -= 6;
			break;
		}
	}
	return x;
}

void drawScrollingText(int window_x, int text_size)
{
	int i, j;
	for (i = 0; i < NUM_COLS; i++)
	{
		for (j = 0; j < 8; j++)
		{
			int num = (i+window_x) % text_size;
			setPixel(i, j+22, display2[num][j]);
		}
	}
}

void transitionUp(int x, int y, char *str)
{
	Color color = WHITE;
	char c;
	int offset = 0;
	int a = x;
	int b = y;
	
	for(int i = 0; i<16; i++)
	{
		clearDisplay();
		offset += 2;
		char *temp = str;
		while ((c = *(temp++)))
		{
			if (c <= WHITE)
			{
				color = c;
			}
			else if (c == '\n')
			{
				a = 1;
				b += 10;
			}
			else
			{
				writeChar(a, b-offset, c, color);
				a += 6;
			}
		}
		delay(10);
	}
}

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