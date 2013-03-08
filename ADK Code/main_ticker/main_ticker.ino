#include "text.h"
#include "display.h"

void setup() {
	Serial3.begin(2400);
	initializeDisplay();
	
	//writeDisplay("\004CPE Student Town Hall | Thurs 2/28 11am-12pm | 38-204\n\002All CPE students are invited. Dr. Smith will provide\nan update on the CPE program.");
	
	char recv_buffer[200];
	char temp_buffer[200];
	int recv_index = 0;
	int c;
	int offset = 0, transition = 0;
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
				for(int j = 0; j<recv_index; j++)
					temp_buffer[j] = recv_buffer[j];
					
				recv_index = 0;
				while(!Serial3.available());
				offset = Serial3.read();
			}
			else if (c == 0x17)
			{
				// stop byte
				recv_buffer[recv_index] = 0;
				clearDisplay();
				writeDisplay(recv_buffer, 2*offset);
				// transitionLeft(1, 2, temp_buffer);
				// transitionLeft(321, 2, recv_buffer);
				//transition up
				if(offset == 201)
				{
					transitionUp(1, 2, temp_buffer);
					transitionUp(1, 34, recv_buffer);
				}
				// else
				// {
					// clearDisplay();
					// writeDisplay(recv_buffer, 2*offset);
				// }
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