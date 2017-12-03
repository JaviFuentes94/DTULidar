#ifndef stepperControl
#define stepperControl

/*Declarations*/
#BYTE portc = 7      // Port used to control motor
BYTE const POSITIONS[4] = { 0b0101, 0b1001, 0b1010, 0b0110 };
unsigned int8 iCurrentPosition = 0; /* This variable keeps track of the current position */
unsigned int32 iDelay = 5000; // delay default 5ms

void initStepper(void);
void stepperRotateSingleRight(void);
void stepperRotateSingleLeft(void);
int16 moveMeasure(int measureTime_ms, int rotation);
void stepperRotate180right(int timeDelay_us);
void stepperRotate180left(int timeDelay_us);


#endif

