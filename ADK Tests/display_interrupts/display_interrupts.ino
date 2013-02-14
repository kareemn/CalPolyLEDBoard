#include "font.h"


#define R1_PIN		30
#define G1_PIN		31
#define B1_PIN		32
#define R2_PIN		34
#define G2_PIN		35
#define B2_PIN		36
#define A_PIN		38 // PD0
#define B_PIN		39 // PD1
#define C_PIN		40 // PD2
#define D_PIN		41 // PD3
#define CLK_PIN	42 // PB6
#define LAT_PIN	43 // PC27
#define OE_PIN		44 // PC28

#define BLACK	0x0
#define RED		0x4
#define GREEN	0x2
#define BLUE	0x1
#define YELLOW	(RED | GREEN)
#define PURPLE	(RED | BLUE)
#define CYAN	(BLUE | GREEN)
#define WHITE	(RED | BLUE | GREEN)

#define TAN    (((WHITE) << 3) | RED)
#define M_BLUE ((BLUE << 3) | BLUE)
#define M_RED  ((RED << 3) | RED)
#define M_YELLOW ((YELLOW << 3) | YELLOW)
#define M_BG   0

#define NUM_SCREENS		10

//   PB5            PB0
//0 0 R1 G1 B1 R2 G2 B2

volatile uint8_t display1[NUM_SCREENS*32*16];
volatile uint8_t display2[NUM_SCREENS*32*16];
volatile uint8_t display3[NUM_SCREENS*32*16];


static uint8_t mario[][12] = {
   {M_BG, M_BG, M_BG, RED, RED, RED, RED, RED, M_BG, M_BG, M_BG, M_BG},
   {M_BG, M_BG, RED, RED, RED, RED, RED, RED, RED, RED, RED, M_BG},
   {M_BG, M_BG, BLACK, BLACK, BLACK, TAN, TAN, BLACK, TAN, M_BG, M_BG, M_BG},
   {M_BG, BLACK, TAN, BLACK, TAN, TAN, TAN, BLACK, TAN, TAN, TAN, M_BG},
   {M_BG, BLACK, TAN, BLACK, BLACK, TAN, TAN, TAN, BLACK, TAN, TAN, TAN},
   {M_BG, BLACK, BLACK, TAN, TAN, TAN, TAN, BLACK, BLACK, BLACK, BLACK, M_BG},
   {M_BG, M_BG, M_BG, TAN, TAN, TAN, TAN, TAN, TAN, TAN, M_BG, M_BG},
   {M_BG, M_BG, M_BLUE, M_BLUE, M_RED, M_BLUE, M_BLUE, M_BLUE, M_BG, M_BG, M_BG, M_BG},
   {M_BG, M_BLUE, M_BLUE, M_BLUE, M_RED, M_BLUE, M_BLUE, M_RED, M_BLUE, M_BLUE, M_BLUE, M_BG},
   {M_BLUE, M_BLUE, M_BLUE, M_BLUE, M_RED, M_BLUE, M_BLUE, M_RED, M_BLUE, M_BLUE, M_BLUE, M_BLUE},
   {TAN, TAN, M_BLUE, M_BLUE, M_RED, M_RED, M_RED, M_RED, M_BLUE, M_BLUE, TAN, TAN},
   {TAN, TAN, TAN, M_RED, M_YELLOW, M_RED, M_RED, M_YELLOW, M_RED, TAN, TAN, TAN},
   {TAN, TAN, M_RED, M_RED, M_RED, M_RED, M_RED, M_RED, M_RED, M_RED, TAN, TAN},
   {M_BG, M_BG, M_RED, M_RED, M_RED, M_BG, M_BG, M_RED, M_RED, M_RED, M_BG, M_BG},
   {M_BG, RED, RED, RED, M_BG, M_BG, M_BG, M_BG, RED, RED, RED, M_BG},
   {RED, RED, RED, RED, M_BG, M_BG, M_BG, M_BG, RED, RED, RED, RED},
};


static inline void pinOutput(int pin, int val)
{
	if (val)
		g_APinDescription[pin].pPort->PIO_SODR = g_APinDescription[pin].ulPin;
	else
		g_APinDescription[pin].pPort->PIO_CODR = g_APinDescription[pin].ulPin;
}

void updateRow(unsigned int row, unsigned int index, volatile uint8_t *display) {
	for (unsigned int x = index; x < index+NUM_SCREENS*32; x++)
	{
      pinOutput(CLK_PIN, 0);
      pinOutput(R1_PIN, display[x] & (1 << 5));
      pinOutput(G1_PIN, display[x] & (1 << 4));
      pinOutput(B1_PIN, display[x] & (1 << 3));
      pinOutput(R2_PIN, display[x] & (1 << 2));
      pinOutput(G2_PIN, display[x] & (1 << 1));
      pinOutput(B2_PIN, display[x] & (1 << 0));
      pinOutput(CLK_PIN, 1);
		
      //PIOB->PIO_CODR = 0x7F; // clears data outputs including setting clock low
		//PIOB->PIO_SODR = display[x]; // outputs data
		//PIOB->PIO_SODR = (1 << 6); // set clock high
	}
	// toggle latch
	pinOutput(LAT_PIN, 1); 
	pinOutput(LAT_PIN, 0);
	
	// Set the row address
	PIOD->PIO_CODR = 0xf;
	PIOD->PIO_SODR = row;
}


//TC1 ch 0
volatile unsigned int frame = 0;
void TC3_Handler()
{
	pinOutput(13, 1);
	long dummy = REG_TC1_SR0;
	pinOutput(OE_PIN, 0); // set OE low
	for (unsigned int i = 0; i < 16; i++)
	{
      if (frame == 0)
         updateRow(i, i*NUM_SCREENS*32, display1);
      else if (frame == 1)
         updateRow(i, i*NUM_SCREENS*32, display2);
      else if (frame == 2)
         updateRow(i, i*NUM_SCREENS*32, display3);
	}
	pinOutput(OE_PIN, 1); // set OE high
	pinOutput(13, 0);
   frame = (frame + 1) & 3;
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
   if (y >= 32 || x >= NUM_SCREENS*32)
   {
      return;
   }

   uint8_t color1, color2;
   color1 = color >> 3 & 0x7;
   color2 = color & 0x7;
	uint8_t temp;
	if (y >= 16)
	{
		y -= 16;
		display1[y*NUM_SCREENS*32+x] = (display1[y*NUM_SCREENS*32+x] & (0x7 << 3)) | color1;
		display2[y*NUM_SCREENS*32+x] = (display2[y*NUM_SCREENS*32+x] & (0x7 << 3)) | color2;
		display3[y*NUM_SCREENS*32+x] = (display3[y*NUM_SCREENS*32+x] & (0x7 << 3)) | (color1 & color2);
	}
	else
	{
		display1[y*NUM_SCREENS*32+x] = (display1[y*NUM_SCREENS*32+x] & 0x7) | (color1 << 3);
		display2[y*NUM_SCREENS*32+x] = (display2[y*NUM_SCREENS*32+x] & 0x7) | (color2 << 3);
		display3[y*NUM_SCREENS*32+x] = (display3[y*NUM_SCREENS*32+x] & 0x7) | ((color1 & color2) << 3);
	}
}

void fillScreen(int num, uint8_t color)
{
	int i, j;
	for (i = num*32; i < (num+1)*32; i++)
	{
		for (j = 0; j < 32; j++)
		{
			setPixel(i, j, color);
		}
	}
}


void writeChar(int x, int y, uint8_t c, uint8_t color, uint8_t bg)
{
	for (int8_t i=0; i<6; i++ ) {
		uint8_t line;
		if (i == 5) 
			line = 0x0;
		else 
			line = font[(c*5)+i];
		
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
	uint8_t x = 0, y = 16;
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

void clearMario(int startX)
{
   if (startX < 0)
      return;
   
   for (int x = 0; x < 24; x++)
   {
      for (int y = 0; y < 32; y++)
      {
         setPixel(startX+x, y, 0);
      }
   }
}

void printMario(int startX)
{
   for (int x = 0; x < 24; x++)
   {
      for (int y = 0; y < 32; y++)
      {
         setPixel(startX+x, y, mario[y/2][x/2]);
      }
   }
}


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
	
   // for (int i = 0; i < 64; i++)
   // {
      // for (int j = 0; j < 5; j++)
      // {
         // int x = i * 5 + j;
         // for (int y = 0; y < 32; y++)
            // setPixel(x, y, i);
      // }
   // }
   
   for (int i = 0; i < NUM_SCREENS; i++)
   {
      fillScreen(i, BLACK);
   }
   while(1)
   {
      for (int i = 0; i <= NUM_SCREENS*32; i++)
      {
         clearMario(i-1);
         printMario(i);
         delay(20);
      }
   }
   //writeStr(0, 2, "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz", WHITE, BLACK);
   //writeStr(0, 12, "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz", WHITE, BLACK);
   //writeStr(0, 22, "ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz", WHITE, BLACK);
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

void loop()
{
}