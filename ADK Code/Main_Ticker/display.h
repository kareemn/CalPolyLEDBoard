#define SCREEN_WIDTH		32
#define SCREEN_HEIGHT	32
#define NUM_SCREENS		10
#define NUM_COLS			(NUM_SCREENS*SCREEN_WIDTH)

#define COLOR1_MASK		0x1C000000	//green, blue, red
#define COLOR2_MASK		0x00000340	//green, red, blue
#define CLK_MASK			0x1;
#define ADDR_MASK			0x3c;
#define R1_PIN		30	// PC28
#define G1_PIN		32	// PC26
#define B1_PIN		31	// PC27
#define R2_PIN		34	// PB8
#define G2_PIN		36	// PB6
#define B2_PIN		35	// PB9
#define A_PIN		38	// PB4
#define B_PIN		39	// PB5
#define C_PIN		40	// PB2
#define D_PIN		41	// PB3
#define CLK_PIN	42	// PB0
#define LAT_PIN	43	// PB1
#define OE_PIN		44 // PA29

#define BLACK	0x0
#define RED		0x4
#define GREEN	0x1
#define BLUE	0x2
#define YELLOW	(RED | GREEN)
#define PURPLE	(RED | BLUE)
#define CYAN	(BLUE | GREEN)
#define WHITE	(RED | BLUE | GREEN)

typedef unsigned char Color;

void initializeDisplay();
void setPixel(int, int, Color);