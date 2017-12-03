#include "stepperControl.h"

void initStepper()
{
   set_tris_c(0xF0);
}


void stepperRotateSingleRight(int motor)
{
     iCurrentPosition = ((iCurrentPosition+1)&3);
     
     /* Set outputs to move the motor */
   if(motor == 1)
   {
      portc = POSITIONS[iCurrentPosition];
   }
   else
   {
      portd = POSITIONS[iCurrentPosition];
   }   
     
}

void stepperRotateSingleLeft(int motor)
{
   if(iCurrentPosition == 0)
   {
      iCurrentPosition = 3;
   }
   else
   {
      iCurrentPosition = ((iCurrentPosition-1)&3);
   }
   if(motor == 1)
   {
      portc = POSITIONS[iCurrentPosition];
   }
   else
   {
      portd = POSITIONS[iCurrentPosition];
   }

}   
/*
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
}*/

void stepperRotate180right(int timeDelay_us, int motor)
{
    for(unsigned int8 i = 1; i<=100; i++)
    {
      if(motor == 1)
      {
         portc = POSITIONS[((iCurrentPosition + i)&3)];
      }
      else
      {
         portd = POSITIONS[((iCurrentPosition + i)&3)];
      }
        delay_us(timeDelay_us);
    }
}


void stepperRotate180left(int timeDelay_us, int motor)
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
      if(motor == 1)
      {
         portc = POSITIONS[iCurrentPosition];
      }        
      else
      {
         delay_us(timeDelay_us);
      }
   }
}
