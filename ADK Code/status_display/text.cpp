#include "text.h"

void writeChar(int x, int y, char c, Color color)
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

void writeString(TextRow row, char *str)
{
	Color color = WHITE;
	char c;
	int x = 1;
	int y = 2 + (row * 10);
	while ((c = *(str++)))
	{
		writeChar(x, y, c, color);
		x += 6;
	}
}