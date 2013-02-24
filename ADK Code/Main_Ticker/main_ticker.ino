#include "text.h"
#include "display.h"

void setup() {
	Serial3.begin(57600);
	initializeDisplay();
   
	writeDisplay("\004CPE Student Town Hall | Thurs 2/28 11am-12pm | 38-204\n\002All CPE students are invited. Dr. Smith will provide\nan update on the CPE program.");
	// writeString(TOP, "\004CPE Student Town Hall | Thurs 2/28 | 11am | 38-204");
	// writeString(MIDDLE, "\002All CPE students are invited. Dr. Smith will provide");
	// writeString(BOTTOM, "\002an update on the CPE program.");
	
	// int numPixels = writeScrollingText("All Computer Engineering Students are invited to a student town hall on Thursday, February 28th. Dr. Smith will provide an update on the program in an open discussion format.", BLUE);
	// //drawScrollingText(0);
	
	// while(1)
	// for (int i = 0; i < numPixels+320; i++)
	// {
		// drawScrollingText(i, numPixels+320);
		// delay(10);
	// }
	
	//writeString(BOTTOM, "of the winter quarter for CPEs", GREEN);
	
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