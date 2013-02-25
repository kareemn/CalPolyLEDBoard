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

#define BLACK	0x0
#define RED		0x4
#define GREEN	0x2
#define BLUE	0x1
#define YELLOW	(RED | GREEN)
#define PURPLE	(RED | BLUE)
#define CYAN	(BLUE | GREEN)
#define WHITE	(RED | BLUE | GREEN)


typedef unsigned char Color3;

typedef struct {
	unsigned char red;
	unsigned char green;
	unsigned char blue;
} Color;

void initializeDisplay();
void clearDisplay();
void setPixel(int, int, Color);