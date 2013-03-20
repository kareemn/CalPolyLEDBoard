#include "display.h"
#include "text.h"
#include <arduino.h>

volatile Color3 display[15][32][32];
volatile int timer_count = 0;
volatile int activated = 1;

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
			if (frame[x][y+8]&0x4)
				tmp |= (1 << 8);
			if (frame[x][y+8]&0x2)
				tmp |= (1 << 9);
			if (frame[x][y+8]&0x1)
				tmp |= (1 << 6);
			PIOB->PIO_SODR = tmp;
		}
		else
		{
			PIOB->PIO_CODR = 0x340;
			PIOC->PIO_CODR = 0x7 << 26;
			PIOC->PIO_SODR = frame[x-32][y+16] << 26;
			int tmp = 0;
			if (frame[x-32][y+24]&0x4)
				tmp |= (1 << 8);
			if (frame[x-32][y+24]&0x2)
				tmp |= (1 << 9);
			if (frame[x-32][y+24]&0x1)
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
volatile int frame = 0, ticks = 0, elapsed_seconds = 0;

void TC3_Handler()
{
	long dummy = REG_TC1_SR0;
	ticks++;
   if (ticks == 1000)
   {
		elapsed_seconds++;
      ticks = 0;
   }
   if (!activated)
      return;
	pinOutput(OE_PIN, 0);
	for (int y = 0; y < 8; y++)
	{
		updateRow(y, display[frame]);
	}
	pinOutput(OE_PIN, 1);
	frame = (frame + 1) % 15;
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
			display[frame][x][y] |= 0x4;
		}
		if (color.green > frame)
		{
			display[frame][x][y] |= 0x2;
		}
		if (color.blue > frame)
		{
			display[frame][x][y] |= 0x1;
		}
	}
}

void clearDisplay()
{
	int i, j;
	for (i = 0; i < 32; i++)
	{
		for (j = 0; j < 32; j++)
		{
			setPixel(i, j, {0, 0, 0});
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

	startTimer(TC1, 0, TC3_IRQn, 1000);

	clearDisplay();
}

void drawLogo()
{
/* Set up white background */
	for(int x = 0; x<32; x++)
	{
		for(int y = 0; y<16; y++)
		{
			setPixel(x, y, {1,1,1});
		}
	}
	
	/* Set up clock frame */
	for(int a = 5; a < 27; a++)
	{
		setPixel(a, 2, BLACK);
		setPixel(a, 12, BLACK);
	}
	
	/* Sets up clock logo background, and left and right sides of clock frame */
	for(int i = 3; i<12; i++)
	{	
		setPixel(4, i, BLACK);
		setPixel(27, i, BLACK);
		for(int j = 5; j<27; j++)
		{
			setPixel(j, i, {2,2,5});
		}
	}
	
	/* Sets clock stand */
	for(int k = 8; k<24; k++)
		setPixel(k, 13, {2,2,5}); 
	
	/* This is 'C' */
	for(int l = 5; l<10; l++)
		setPixel(7, l, GREEN);
	
	for(int m = 8; m<12; m++)
	{
		setPixel(m, 4, GREEN);
		setPixel(m, 10, GREEN);
	}
	
	/* This is the colon */
	setPixel(13, 5, GREEN);
	setPixel(13, 9, GREEN);
	
	/* This is the 'P' */
	for(int n = 4; n<11; n++)
		setPixel(15, n, GREEN);
		
	for(int o = 16; o<19; o++)
	{
		setPixel(o, 4, GREEN);
		setPixel(o, 7, GREEN);
	}
	
	for(int p = 5; p<7; p++)
		setPixel(19, p, GREEN);
		
	/* This is the 'E' */
	for(int q = 4; q<11; q++)
		setPixel(21, q, GREEN);
		
	for(int r = 22; r<26; r++)
	{
		setPixel(r, 4, GREEN);
		setPixel(r, 10, GREEN);
	}
	
	for(int s = 22; s<25; s++)
		setPixel(s, 7, GREEN);
}

void clearBox(int startX, int startY, int endX, int endY)
{
   int x, y;
   for (x = startX; x <= endY; x++)
   {
      for (y = startY; y <= endY; y++)
      {
         setPixel(x, y, BLACK);
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