#include "font.h"


#define R1_PIN		30
#define R2_PIN		31
#define B1_PIN		32
#define B2_PIN		33
#define G1_PIN		34
#define G2_PIN		35
#define A_PIN		36
#define B_PIN		37
#define C_PIN		38
#define CLK_PIN	39
#define LAT_PIN	40
#define OE_PIN		41

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

#define NUM_SCREENS	3
#define ON_TIME		7

volatile uint8_t display[NUM_SCREENS*32][16];


static inline void pinOutput(int pin, int val)
{
	if (val)
		g_APinDescription[pin].pPort->PIO_SODR = g_APinDescription[pin].ulPin;
	else
		g_APinDescription[pin].pPort->PIO_CODR = g_APinDescription[pin].ulPin;
}

void updateRow(int row, int isBlack) {
	pinOutput(OE_PIN, 0);

	// Set the row address
	pinOutput(A_PIN, row&0x1);
	pinOutput(B_PIN, row&0x2);
	pinOutput(C_PIN, row&0x4);

	for (int x = 0; x < NUM_SCREENS*32; x++)
	{
		pinOutput(CLK_PIN, 0);
		if (isBlack)
		{
			pinOutput(R1_PIN, 0);
			pinOutput(G1_PIN, 0);
			pinOutput(B1_PIN, 0);
			pinOutput(R2_PIN, 0);
			pinOutput(G2_PIN, 0);
			pinOutput(B2_PIN, 0);
		}
		else
		{
			// This will end up on the display closest to the arduino
			pinOutput(R1_PIN, display[x][row]&RED);
			pinOutput(G1_PIN, display[x][row]&GREEN);
			pinOutput(B1_PIN, display[x][row]&BLUE);
			pinOutput(R2_PIN, display[x][row+8]&RED);
			pinOutput(G2_PIN, display[x][row+8]&GREEN);
			pinOutput(B2_PIN, display[x][row+8]&BLUE);
		}
      pinOutput(CLK_PIN, 1);
	}
	pinOutput(LAT_PIN, 1);
	pinOutput(LAT_PIN, 0);
	pinOutput(OE_PIN, 1);
}


//TC1 ch 0
volatile bool l;
volatile int count = 0;
void TC3_Handler()
{
	long dummy= REG_TC1_SR0;
	for (int i = 0; i < 8; i++)
	{
		if (count == 0)
		{
			updateRow(i, 0);
		}
		else
		{
			updateRow(i, 1);
		}
	}
	if (++count == ON_TIME)
	{
		count = 0;
	}
	pinOutput(13, (l = !l));
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

void fillScreen(int num, uint8_t color)
{
	int i, j;
	for (i = num*32; i < (num+1)*32; i++)
	{
		for (j = 0; j < 16; j++)
		{
			display[i][j] = color;
		}
	}
}

void fillHalf(int num, int half, uint8_t color)
{
	int i, j;
	for (i = num*32; i < (num+1)*32; i++)
	{
		for (j = 0; j < 8; j++)
		{
			if (half)
			{
				display[i][j+8] = color;
			}
			else
			{
				display[i][j] = color;
			}
		}
	}
}

void writeChar(int x, int y, uint8_t c, uint8_t color, uint8_t bg)
{
	y--;
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
				display[x+i][y+j-1] = color;
			}
			else
			{
				display[x+i][y+j-1] = bg;
			}
			line >>= 1;
		}
		// if (tmp & 0x1) 
		// {
			// display[x+i][y+7] = color;
		// }
		// else
		// {
			// display[x+i][y+7] = bg;
		// }
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
	uint8_t x = 0, y = 8;
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

void setup() {
	Serial3.begin(9600);

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
	pinMode(LAT_PIN,OUTPUT);

	pinOutput(A_PIN, 0);
	pinOutput(B_PIN, 0);
	pinOutput(C_PIN, 0);
	pinOutput(LAT_PIN, 0);
	pinOutput(OE_PIN, 0);
	pinOutput(CLK_PIN, 1);
	
	uint8_t i;
	for (i = 0; i < NUM_SCREENS; i++)
	{
		fillScreen(i, BLACK);
	}
	
	pinMode(13,OUTPUT);
	startTimer(TC1, 0, TC3_IRQn, 500); //TC1 channel 0, the IRQ for that channel and the desired frequency

	while(1)
	{
		if (Serial3.available())
		{
			char c = Serial3.read();
			writeChar(4, 8, c, WHITE, BLACK);
			writeChar(36, 8, c, WHITE, BLACK);
			writeChar(68, 8, c, WHITE, BLACK);
		}
	}
}

void loop()
{
}