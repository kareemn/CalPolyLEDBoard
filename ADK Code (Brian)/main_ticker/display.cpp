#include "display.h"
#include <arduino.h>

volatile Color display[16][NUM_COLS];
volatile int activated = 1;

// sets an output pin low / high efficiently
inline void pinOutput(int pin, int val)
{
	if (val)
		g_APinDescription[pin].pPort->PIO_SODR = g_APinDescription[pin].ulPin;
	else
		g_APinDescription[pin].pPort->PIO_CODR = g_APinDescription[pin].ulPin;
}

// updates an entire row of LEDs
void updateRow(int y) {
	int temp;
	for (int x = 0; x < NUM_COLS; x++)
	{
		PIOB->PIO_CODR = COLOR2_MASK | CLK_MASK;
		PIOC->PIO_CODR = COLOR1_MASK;
		temp = (uint32_t)display[y][x] << 22;
		PIOC->PIO_SODR = temp & COLOR1_MASK;
		temp = (uint32_t)display[y][x] << 6;
		PIOB->PIO_SODR = (temp & COLOR2_MASK) | CLK_MASK;
	}
	// toggle latch
	pinOutput(LAT_PIN, 1); 
	pinOutput(LAT_PIN, 0);
	
	// This seems like it'd be slow, but gets optimized nicely
	PIOB->PIO_CODR = ADDR_MASK;
	temp = 0;
	if (y & (1 << 0))
		temp |= (1 << 4);
	if (y & (1 << 1))
		temp |= (1 << 5);
	if (y & (1 << 2))
		temp |= (1 << 2);
	if (y & (1 << 3))
		temp |= (1 << 3);
	PIOB->PIO_SODR = temp;
}

//timer interrupt handler
volatile unsigned long ticks = 0;
void TC3_Handler()
{
	long dummy = REG_TC1_SR0;
   ticks++;
   if (!activated)
      return;
	pinOutput(OE_PIN, 0); // set OE low
	for (int i = 0; i < 16; i++)
	{
      updateRow(i);
	}
	pinOutput(OE_PIN, 1); // set OE high
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
   NVIC_EnableIRQ(TC3_IRQn);
}

void initializeDisplay()
{
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
	
	clearDisplay();
	startTimer(TC1, 0, TC3_IRQn, 100); //TC1 channel 0, the IRQ for that channel and the desired frequency
   displayOn();
}

void setPixel(int x, int y, Color color)
{
   if (y >= 32 || x >= NUM_COLS || x < 0 || y < 0)
   {
      return;
   }

	if (y >= 16)
	{
		y -= 16;
		int red = color & RED;
		int blue = color & BLUE;
		int green = color & GREEN;
		color = 0;
		if (red)
			color |= (1 << 2);
		if (green)
			color |= (1 << 0);
		if (blue)
			color |= (1 << 3);
		display[y][x] = (display[y][x] & (0x7 << 4)) | color;
	}
	else
	{
		display[y][x] = (display[y][x] & 0xf) | (color << 4);
	}
}

void clearDisplay()
{
	int i, j;
	for (i = 0; i < NUM_COLS; i++)
	{
		for (j = 0; j < 16; j++)
		{
			display[j][i] = 0;
		}
	}
}

void shiftDisplayLeft()
{
	for (int col = 0; col < 320; col++)
	{
		if (col == 319)
		{
			for (int row = 0; row < 16; row++)
			{
				display[row][col] = 0;
			}
		}
		else
		{
			for (int row = 0; row < 16; row++)
			{
				display[row][col] = display[row][col+1];
			}
		}
	}
}
void shiftDisplayRight()
{
	for (int col = 319; col >= 0; col--)
	{
		if (col == 0)
		{
			for (int row = 0; row < 16; row++)
			{
				display[row][col] = 0;
			}
		}
		else
		{
			for (int row = 0; row < 16; row++)
			{
				display[row][col] = display[row][col-1];
			}
		}
	}
}

void displayOn()
{
   activated = 1;
}

void displayOff()
{
   activated = 0;
}