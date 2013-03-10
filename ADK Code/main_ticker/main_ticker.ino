#include "text.h"
#include "display.h"

void setup() {
	Serial3.begin(3000);
	Serial.begin(57600);
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
				int j = 0;
				for(int i = 0; i<200; i++)
					temp_buffer[i] = 0;
					
				
				for(j = 0; recv_buffer[j]; j++)
					 temp_buffer[j] = recv_buffer[j];
				
				temp_buffer[j] = 0;
				
				Serial.println(recv_index);
				Serial.println(recv_buffer);
				Serial.println(temp_buffer);
					
				recv_index = 0;
				while(!Serial3.available());
				offset = Serial3.read();
			}
			else if (c == 0x17)
			{
				// stop byte
				recv_buffer[recv_index] = 0;
					
				clearDisplay();
				writeDisplay(1 + (2*offset), 2, recv_buffer);
				// transitionLeft(1, 2, temp_buffer);
				// transitionLeft(321, 2, recv_buffer);
				//transition up
				// if(offset == 201)
				// {
					// //transitionUp(1, 2, temp_buffer);
					// //transitionUp(1, 34, recv_buffer);
					// clearDisplay();
					// writeDisplay(1, 2, recv_buffer);
				// }
				if(offset == 202)
				{
					transitionRight(1, 2, temp_buffer);
					transitionRight(-319, 2, recv_buffer);
					delay(500);
				}
				else if(offset == 203)
				{
					transitionLeft(1, 2, temp_buffer);
					transitionLeft(321, 2, recv_buffer);
					delay(500);
				}
				// else
				// {
					// clearDisplay();
					// writeDisplay(1 + (2*offset), 2, recv_buffer);
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