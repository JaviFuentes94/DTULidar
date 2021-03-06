#include "stepperControl.h"


void initStepper()
{
   set_tris_c(0xF0);
   set_tris_d(0xF0);
}

void stepperMotorSequenceBottom()
{
   stepperRotateSingleLeft(BOTTOM_MOTOR);
   iGlobalPosition[BOTTOM_MOTOR]++;
   bGlobalGoUp = !bGlobalGoUp;
   delay_ms(1000);

   if(iGlobalPosition[BOTTOM_MOTOR] == BOTTOM_MOTOR_LIMIT)
   {
      bSequenceOver = True;
   }
}

void stepperMotorSequence(signed int8 * angleX, signed int8 * angleZ)
{
   if(bSequenceOver)
   {
      return;
   }

   if(bGlobalGoUp == TRUE)
   {
      if(iGlobalPosition[TOP_MOTOR] == TOP_MOTOR_LIMIT)
      {
         stepperMotorSequenceBottom();
      }
      else
      {
         stepperRotateSingleRight(TOP_MOTOR);      
         iGlobalPosition[TOP_MOTOR]++;         
      }
   }
   else
   {
      if(iGlobalPosition[TOP_MOTOR] == (-1*TOP_MOTOR_LIMIT))
      {
         stepperMotorSequenceBottom();
      }
      else
      {
         stepperRotateSingleLeft(TOP_MOTOR);      
         iGlobalPosition[TOP_MOTOR]--;               
      }
   }
   
   *angleZ = iGlobalPosition[BOTTOM_MOTOR];
   *angleX = iGlobalPosition[TOP_MOTOR];
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
