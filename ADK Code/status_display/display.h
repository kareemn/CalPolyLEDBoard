#ifndef DISPLAY_H
#define DISPLAY_H

#define R1_PIN		30	// PC28
#define G1_PIN		31	// PC27
#define B1_PIN		32	// PC26
#define R2_PIN		34	// PB8
#define G2_PIN		35	// PB9
#define B2_PIN		36	// PB6
#define A_PIN		38	// PB4
#define B_PIN		39	// PB5
#define C_PIN		40	// PB2
#define CLK_PIN	42	// PB0
#define LAT_PIN	43	// PB1
#define OE_PIN		44 // PA29

#define BLACK	{0, 0, 0}
#define RED		{15, 0, 0}
#define GREEN	{0, 15, 0}
#define BLUE	{0, 0, 15}
#define YELLOW	{15, 15, 0}
#define PURPLE	{15, 0, 15}
#define CYAN	{0, 15, 15}
#define WHITE	{15, 15, 15}

typedef unsigned char Color3;

typedef struct {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} Color;

void initializeDisplay();
void clearDisplay();
void setPixel(int, int, Color);
void drawLogo();
int updateTimerCount();

extern volatile int elapsed_seconds;
#endif