

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

#define ON_TIME	7


static inline void pinOutput(int pin, int val)
{
	if (val)
		g_APinDescription[pin].pPort->PIO_SODR = g_APinDescription[pin].ulPin;
	else
		g_APinDescription[pin].pPort->PIO_CODR = g_APinDescription[pin].ulPin;
}

void updateRow(int i, int topColor, int color1, int color2, int color3) {
	pinOutput(OE_PIN, 0);

	// Set the row address
	pinOutput(A_PIN, i&0x1);
	pinOutput(B_PIN, i&0x2);
	pinOutput(C_PIN, i&0x4);

	for (int x = 0; x < 96; x++)
	{
		pinOutput(CLK_PIN, 0);
		if (x > 63)
		{
			// This will end up on the display farthest from the arduino
			pinOutput(R1_PIN, topColor&RED);
			pinOutput(G1_PIN, topColor&GREEN);
			pinOutput(B1_PIN, topColor&BLUE);
			pinOutput(R2_PIN, color1&RED);
			pinOutput(G2_PIN, color1&GREEN);
			pinOutput(B2_PIN, color1&BLUE);
		}
		else if (x > 31)
		{
			// This will end up on the middle display
			pinOutput(R1_PIN, topColor&RED);
			pinOutput(G1_PIN, topColor&GREEN);
			pinOutput(B1_PIN, topColor&BLUE);
			pinOutput(R2_PIN, color2&RED);
			pinOutput(G2_PIN, color2&GREEN);
			pinOutput(B2_PIN, color2&BLUE);
		}
		else
		{
			// This will end up on the display closest to the arduino
			pinOutput(R1_PIN, topColor&RED);
			pinOutput(G1_PIN, topColor&GREEN);
			pinOutput(B1_PIN, topColor&BLUE);
			pinOutput(R2_PIN, color3&RED);
			pinOutput(G2_PIN, color3&GREEN);
			pinOutput(B2_PIN, color3&BLUE);
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
			updateRow(i, TOP_COLOR, COLOR1, COLOR2, COLOR3);
		}
		else
		{
			updateRow(i, 0, 0, 0, 0);
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

void setup() {
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
	
	pinMode(13,OUTPUT);
	startTimer(TC1, 0, TC3_IRQn, 500); //TC1 channel 0, the IRQ for that channel and the desired frequency

	while(1);
}

void loop()
{
}