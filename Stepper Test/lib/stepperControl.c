#include "stepperControl.h"


void initStepper()
{
   set_tris_c(0xF0);
   set_tris_d(0xF0);
}

void stepperMotorSequenceTop()
{
   stepperRotateSingleRight(TOP_MOTOR);
   iGlobalPosition[TOP_MOTOR]++;
   bGlobalGoRight = !bGlobalGoRight;

   if(iGlobalPosition[TOP_MOTOR] == TOP_MOTOR_LIMIT)
   {
      bSequenceOver = True;
   }
}

void stepperMotorSequence()
{
   if(bSequenceOver)
   {
      return;
   }

   if(bGlobalGoRight == TRUE)
   {
      if(iGlobalPosition[BOTTOM_MOTOR] == BOTTOM_MOTOR_LIMIT)
      {
         stepperMotorSequenceTop();
      }
      else
      {
         stepperRotateSingleRight(BOTTOM_MOTOR);      
         iGlobalPosition[BOTTOM_MOTOR]++;         
      }
   }
   else
   {
      if(iGlobalPosition[BOTTOM_MOTOR] == (-1*BOTTOM_MOTOR_LIMIT))
      {
         stepperMotorSequenceTop();
      }
      else
      {
         stepperRotateSingleLeft(BOTTOM_MOTOR);      
         iGlobalPosition[BOTTOM_MOTOR]--;               
      }
   }
}

void stepperRotateSingleRight(int1 motor)
{
   iCurrentState[motor] = ((iCurrentState[motor]+1)&3);
     
     /* Set outputs to move the motor */
   if(motor == 1)
   {
      portc = POSITIONS[iCurrentState[motor]];
   }
   else
   {
      portd = POSITIONS[iCurrentState[motor]];
   }        
}

void stepperRotateSingleLeft(int1 motor)
{
   if(iCurrentState[motor] == 0)
   {
      iCurrentState[motor] = 3;
   }
   else
   {
      iCurrentState[motor] = ((iCurrentState[motor]-1)&3);
   }
   if(motor == 1)
   {
      portc = POSITIONS[iCurrentState[motor]];
   }
   else
   {
      portd = POSITIONS[iCurrentState[motor]];
   }

}   

void stepperRotate180right(int timeDelay_us, int1 motor)
{
    for(unsigned int8 i = 1; i<=100; i++)
    {
      if(motor == 1)
      {
         portc = POSITIONS[((iCurrentState[motor] + i)&3)];
      }
      else
      {
         portd = POSITIONS[((iCurrentState[motor] + i)&3)];
      }
        delay_us(timeDelay_us);
    }
}


void stepperRotate180left(int timeDelay_us, int1 motor)
{
   for(unsigned int8 i = 1; i<=100; i++)
   {
      if(iCurrentState[motor] == 0)
      {
         iCurrentState[motor] = 3;
      }
      else
      {
         iCurrentState[motor] = ((iCurrentState[motor]-1)&3);
      }
      if(motor == 1)
      {
         portc = POSITIONS[iCurrentState[motor]];
      }        
      else
      {
         delay_us(timeDelay_us);
      }
   }
}
