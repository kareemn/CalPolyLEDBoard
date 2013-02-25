#include "display.h"
#include <arduino.h>

volatile Color3 display[15][32][32];

static inline void pinOutput(int pin, int val)
{
	if (val)
		g_APinDescription[pin].pPort->PIO_SODR = g_APinDescription[pin].ulPin;
	else
		g_APinDescription[pin].pPort->PIO_CODR = g_APinDescription[pin].ulPin;
}

void updateRow(int y, volatile Color3 frame[32][32])
{
	int temp;
	for (int x = 0; x < 64; x++)
	{
		pinOutput(CLK_PIN, 0);
		if (x < 32)
		{
			PIOB->PIO_CODR = 0x340;
			PIOC->PIO_CODR = 0x7 << 26;
			PIOC->PIO_SODR = frame[x][y] << 26;
			int tmp = 0;
			if (frame[x][y+8]&RED)
				tmp |= (1 << 8);
			if (frame[x][y+8]&GREEN)
				tmp |= (1 << 9);
			if (frame[x][y+8]&BLUE)
				tmp |= (1 << 6);
			PIOB->PIO_SODR = tmp;
		}
		else
		{
			PIOB->PIO_CODR = 0x340;
			PIOC->PIO_CODR = 0x7 << 26;
			PIOC->PIO_SODR = frame[x-32][y+16] << 26;
			int tmp = 0;
			if (frame[x-32][y+24]&RED)
				tmp |= (1 << 8);
			if (frame[x-32][y+24]&GREEN)
				tmp |= (1 << 9);
			if (frame[x-32][y+24]&BLUE)
				tmp |= (1 << 6);
			PIOB->PIO_SODR = tmp;
		}
      pinOutput(CLK_PIN, 1);
	}
	pinOutput(LAT_PIN, 1);
	pinOutput(LAT_PIN, 0);
	
	// Set the row address
	pinOutput(A_PIN, y&0x1);
	pinOutput(B_PIN, y&0x2);
	pinOutput(C_PIN, y&0x4);
}

//TC1 ch 0
volatile int frame = 0;
void TC3_Handler()
{
	long dummy = REG_TC1_SR0;
	pinOutput(13, 1);
	pinOutput(OE_PIN, 0);
	for (int y = 0; y < 8; y++)
	{
		updateRow(y, display[frame]);
	}
	pinOutput(OE_PIN, 1);
	frame = (frame + 1) % 15;
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

void setPixel(int x, int y, Color color)
{
	for (int frame = 0; frame < 15; frame++)
	{
		display[frame][x][y] = 0;
		if (color.red > frame)
		{
			display[frame][x][y] = RED;
		}
		if (color.green > frame)
		{
			display[frame][x][y] = GREEN;
		}
		if (color.blue > frame)
		{
			display[frame][x][y] = BLUE;
		}
	}
}

void fillScreen(Color color)
{
	int i, j;
	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 32; j++)
		{
			setPixel(i, j, color);
		}
	}
}

void initializeDisplay()
{
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
	
	int r, g, b;
	for (int i = 0; i < 32; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			Color c = {i>>1, j>>1, i&0xf};
			setPixel(i, j, c);
		}
	}
	
	// Color c1 = {0x1, 0, 0};
	// Color c2 = {0, 0x2, 0};
	// fillScreen(c1);
	// for (int i = 0; i < 32; i++)
		// setPixel(i, i, c2);
	
	startTimer(TC1, 0, TC3_IRQn, 1000);
	while(1);
}