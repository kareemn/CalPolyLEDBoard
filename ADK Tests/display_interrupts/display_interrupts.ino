#include "font.h"


#define R1_PIN		42
#define G1_PIN		43
#define B1_PIN		40
#define R2_PIN		41
#define G2_PIN		38
#define B2_PIN		39
#define A_PIN		24
#define B_PIN		25
#define C_PIN		26
#define D_PIN		27
#define CLK_PIN	36
#define LAT_PIN	31
#define OE_PIN		32

#define BLACK	0x0
#define RED		0x1
#define GREEN	0x2
#define BLUE	0x4
#define YELLOW	0x3
#define PURPLE	0x5
#define CYAN	0x6
#define WHITE	0x7
#define TOP_COLOR	WHITE
#define COLOR1		RED
#define COLOR2		BLUE
#define COLOR3		CYAN

#define NUM_SCREENS		1
#define SCREEN_HEIGHT	32

volatile uint8_t display[NUM_SCREENS*32][SCREEN_HEIGHT/2];


static inline void pinOutput(int pin, int val)
{
	if (val)
		g_APinDescription[pin].pPort->PIO_SODR = g_APinDescription[pin].ulPin;
	else
		g_APinDescription[pin].pPort->PIO_CODR = g_APinDescription[pin].ulPin;
}

void updateRow(int row) {
	pinOutput(OE_PIN, 0); // set OE low

	for (int x = 0; x < NUM_SCREENS*32; x++)
	{
		PIOB->PIO_CODR = 0x7F; // clears data outputs including setting clock low
		PIOB->PIO_SODR = display[x][row]; // outputs data
      pinOutput(CLK_PIN, 1); // clock high
	}
	// toggle latch
	pinOutput(LAT_PIN, 1); 
	pinOutput(LAT_PIN, 0);
	pinOutput(OE_PIN, 1); // set OE hig
	
	// Set the row address
	PIOD->PIO_CODR = 0xf;
	PIOD->PIO_SODR = row;
}


//TC1 ch 0
void TC3_Handler()
{
	pinOutput(13, 1);
	long dummy = REG_TC1_SR0;
	for (int i = 0; i < SCREEN_HEIGHT/2; i++)
	{
		updateRow(i);
	}
	pinOutput(13, 0);
}

void startTimer(Tc *tc, uint32_t channel, IRQn_Type irq, uint32_t frequency) {
	pmc_set_writeprotect(false);
	pmc_enable_periph_clk((uint32_t)irq);
	TC_Configure(tc, channel, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK4);
	uint32_t rc = VARIANT_MCK/128/frequency; //128 because we selected TIMER_CLOCK4 above
	tc->TC_CHANNEL[channel].TC_RA = rc/2;
	tc->TC_CHANNEL[channel].TC_RC = rc;
	TC_Start(tc, channel);
	tc->TC_CHANNEL[channel].TC_IER=TC_IER_CPCS;
	tc->TC_CHANNEL[channel].TC_IDR=~TC_IER_CPCS;
	NVIC_EnableIRQ(irq);
}

void setPixel(int x, int y, uint8_t color)
{
	color &= 7;
	uint8_t temp;
	if (y >= SCREEN_HEIGHT/2)
	{
		y -= SCREEN_HEIGHT/2;
		temp = display[x][y] & 0x7;
		color <<= 3;
		display[x][y] = temp | color;
	}
	else
	{
		temp = display[x][y] & (0x7 << 3);
		display[x][y] = temp | color;
	}
}

void fillScreen(int num, uint8_t color)
{
	int i, j;
	for (i = num*32; i < (num+1)*32; i++)
	{
		for (j = 0; j < SCREEN_HEIGHT/2; j++)
		{
			setPixel(i, j, color);
		}
	}
}

/*
void writeChar(int x, int y, uint8_t c, uint8_t color, uint8_t bg)
{
	for (int8_t i=0; i<6; i++ ) {
		uint8_t line;
		if (i == 5) 
			line = 0x0;
		else 
			line = font[(c*5)+i];
		
		//uint8_t tmp = line & 0x1;
		for (int8_t j = 0; j<8; j++) {
			if (line & 0x1) 
			{
				setPixel(x+i, y+j, color);
			}
			else
			{
				setPixel(x+i, y+j, bg);
			}
			line >>= 1;
		}
	}
}

void writeStr(int x, int y, char *str, uint8_t color, uint8_t bg)
{
	uint8_t c;
	while ((c = *(str++)))
	{
		writeChar(x, y, c, color, bg);
		x += 6;
	}
}

//will continue to write till NULL encountered
void TopString(char *str, uint8_t color)
{
	uint8_t c; 
	uint8_t x = 0, y = 0;
	while ((c = *(str++)))
	{
		writeChar(x, y, c, color, BLACK);
		x += 6;
		if(x+5 > NUM_SCREENS*32)
		{
			x = 0;
			return;
		}
	}
   
}

void BottomString(char *str, uint8_t color)
{
	uint8_t c; 
	uint8_t x = 0, y = SCREEN_HEIGHT/2;
	while ((c = *(str++)))
	{
		writeChar(x, y, c, color, BLACK);
		x += 6;
		if(x+5 > NUM_SCREENS*32)
		{
			x = 0;
			return;
		}
	}
}
*/

void setup() {
	Serial3.begin(57600);

	pinMode(13, OUTPUT);
	pinOutput(13, LOW);
	
	pinMode(R1_PIN,OUTPUT);
	pinMode(G1_PIN,OUTPUT);
	pinMode(B1_PIN,OUTPUT);
	pinMode(R2_PIN,OUTPUT);
	pinMode(G2_PIN,OUTPUT);
	pinMode(B2_PIN,OUTPUT);
	pinMode(CLK_PIN,OUTPUT);
	pinMode(OE_PIN,OUTPUT);
	pinMode(A_PIN,OUTPUT);
	pinMode(B_PIN,OUTPUT);
	pinMode(C_PIN,OUTPUT);
	pinMode(D_PIN,OUTPUT);
	pinMode(LAT_PIN,OUTPUT);

	pinOutput(A_PIN, 0);
	pinOutput(B_PIN, 0);
	pinOutput(C_PIN, 0);
	pinOutput(D_PIN, 0);
	pinOutput(LAT_PIN, 0);
	pinOutput(OE_PIN, 0);
	pinOutput(CLK_PIN, 1);
	
	startTimer(TC1, 0, TC3_IRQn, 200); //TC1 channel 0, the IRQ for that channel and the desired frequency
	
	for (int i = 0; i < NUM_SCREENS; i++)
	{
		fillScreen(i, WHITE);
	}
	while(1);
	
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

void loop()
{
}