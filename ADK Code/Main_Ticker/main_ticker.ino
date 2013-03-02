#include "text.h"
#include "display.h"

void setup() {
	Serial3.begin(2400);
	initializeDisplay();
	
	//writeDisplay("\004CPE Student Town Hall | Thurs 2/28 11am-12pm | 38-204\n\002All CPE students are invited. Dr. Smith will provide\nan update on the CPE program.");
	
	char recv_buffer[100];
	int recv_index = 0;
	int c;
	int offset = 0;
	while(1)
	{
		if (Serial3.available())
		{
			c = Serial3.read();
			if (c == -1)
			{
				// error, do nothing
			}
			else if (c == 0xc)
			{
				// start byte
				recv_index = 0;
				while(!Serial3.available());
				offset = Serial3.read();
			}
			else if (c == 0x17)
			{
				// stop byte
				recv_buffer[recv_index] = 0;
				clearDisplay();
				writeDisplay(recv_buffer, 6*offset);
			}
			else
			{
				recv_buffer[recv_index++] = c;
			}
		}
	}
}

// will never enter this function, but must be defined
// we just do everyting in setup()
void loop() {}