#define LED_PIN 13
#define TEST_PIN 53

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

static inline void setPin(uint32_t pin)
{
	g_APinDescription[pin].pPort->PIO_SODR = g_APinDescription[pin].ulPin;
}

static inline void clearPin(uint32_t pin)
{
	g_APinDescription[pin].pPort->PIO_CODR = g_APinDescription[pin].ulPin;
}

void setup()
{
	pinMode(LED_PIN, OUTPUT);
	pinMode(TEST_PIN, OUTPUT);
	
	digitalWrite(LED_PIN, HIGH);
	digitalWrite(TEST_PIN, HIGH);
	
	pinMode(R1_PIN, OUTPUT);
	pinMode(R2_PIN, OUTPUT);
	pinMode(G1_PIN, OUTPUT);
	pinMode(G2_PIN, OUTPUT);
	pinMode(B1_PIN, OUTPUT);
	pinMode(B2_PIN, OUTPUT);
	pinMode(A_PIN, OUTPUT);
	pinMode(B_PIN, OUTPUT);
	pinMode(C_PIN, OUTPUT);
	pinMode(OE_PIN, OUTPUT);
	pinMode(LAT_PIN, OUTPUT);
	pinMode(CLK_PIN, OUTPUT);
	
	while(1)
	{
		setPin(OE_PIN);
		setPin(LAT_PIN);
		
		setPin(A_PIN);
		clearPin(B_PIN);
		clearPin(C_PIN);
		
		clearPin(OE_PIN);
		clearPin(LAT_PIN);
		setPin(TEST_PIN);
	
		setPin(R1_PIN);
		clearPin(R2_PIN);
		clearPin(B1_PIN);
		setPin(B2_PIN);
		clearPin(G1_PIN);
		clearPin(G2_PIN);
		setPin(CLK_PIN);
		setPin(R1_PIN);
		clearPin(R2_PIN);
		clearPin(B1_PIN);
		setPin(B2_PIN);
		clearPin(G1_PIN);
		clearPin(G2_PIN);
		clearPin(CLK_PIN);
		clearPin(TEST_PIN);
	}
}

void loop()
{
}
