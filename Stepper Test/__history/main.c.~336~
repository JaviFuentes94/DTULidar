
#include <main.h>

/*Declarations*/
#BYTE portc = 7      // Port used to control motor
BYTE const POSITIONS[4] = { 0b0101, 0b1001, 0b1010, 0b0110 };
unsigned int8 iCurrentPosition = 0; /* This variable keeps track of the current position */
unsigned int32 iDelay = 5000; // delay default 5ms

initStepper()
{
	set_tris_c(0xF0);
}


int16 moveMeasure(int measureTime_ms, int rotation)
{
		delay_ms(measureTime_ms);
		int16 measurement = readLongRangeSensor();
		if(rotation == TRUE)
		{
				stepperRotateSingleRight();
		}
		else	
		{
				stepperRotateSingleLeft();
		}	
		return measurement;
}


void stepperRotateSingleRight()
{
     iCurrentPosition = ((iCurrentPosition+1)&3);
     
     /* Set outputs to move the motor */
     portc = POSITIONS[iCurrentPosition];
}

void stepperRotateSingleLeft()
{
     if(iCurrentPosition == 0)
     {
         iCurrentPosition = 3;
     }
     else
     {
         iCurrentPosition = ((iCurrentPosition-1)&3);
     }
     portc = POSITIONS[iCurrentPosition];
}



void stepperRotate180right(int timeDelay_us)
{
		for(unsigned int8 i = 1; i<=100; i++)
    {
    	portc = POSITIONS[((iCurrentPosition + i)&3)];
      delay_us(timeDelay_us);
    }
}


void stepperRotate180left(int timeDelay_us)
{
		for(unsigned int8 i = 1; i<=100; i++)
    {
       if(iCurrentPosition == 0)
       {
           iCurrentPosition = 3;
       }
       else
       {
           iCurrentPosition = ((iCurrentPosition-1)&3);
       }
       portc = POSITIONS[iCurrentPosition];
			 delay_us(timeDelay_us);
    }
}



void main()
{
		setup_oscillator(OSC_8MHZ,2);
	 
 		initStepper()
  	while(TRUE)
   	{
			int16 moveMeasure(int measureTime, int rotation)
			moveMeasure(100, 1)	// delay 100ms rotate right
   	}
}
