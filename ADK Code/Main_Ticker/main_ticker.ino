#include "text.h"
#include "display.h"

void setup() {
	Serial3.begin(57600);
	initializeDisplay();
   
	writeString(TOP, "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz", RED, BLACK);
	writeString(MIDDLE, "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz", BLUE, BLACK);
	writeString(BOTTOM, "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz", GREEN, BLACK);
	
	while(1);
   // for (int i = 'A'; i < 'Z'; i++)
   // {
      // writeChar(
   // }
	// TopString("Hello world on ten LED matrix displays for CPE capstone.", GREEN);
	// BottomString("Hello world on ten LED matrix displays for CPE capstone.", WHITE);
   // while(1);
	
	// TopString("~~Hello World!~~", WHITE);
	// BottomString("~~Hello World!~~", WHITE);
	// int x = 0, y = 0;
	// while(1)
	// {
		// if (Serial3.available())
		// {
			// char c = Serial3.read();
			// if (c == '\r')
			// {
				// for (int i = 0; i < NUM_SCREENS; i++)
				// {
					// fillScreen(i, BLACK);
				// }
				// y = 0;
				// x = 0;
			// }
			// else if (c == '\n')
			// {
				// y += 8;
				// x = 0;
			// }
			// else
			// {
				// if (x <= NUM_SCREENS*32-6)
				// {
					// writeChar(x, y, c, WHITE, BLACK);
				// }
				// x += 6;
			// }
		// }
	// }
}

// will never enter this function, but must be defined
// we just do everyting in setup()
void loop() {}