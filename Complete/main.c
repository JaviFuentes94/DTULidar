#include <main.h>
#include "lib/stepperControl.c"
#include "lib/sensorControl.c"


void sendMeasurements(signed int8 zAngle, signed int8 xAngle, unsigned int16 distance)
{
   char characterToSend;
   characterToSend = *((char*)&(zAngle));
   putc((int)characterToSend);
   
   characterToSend = *((char*)&(xAngle));
   putc((int)characterToSend);
   
   characterToSend = *((char*)&(distance));
   putc((int)characterToSend);
   characterToSend = *(((char*)&(distance))+1);
   putc((int)characterToSend);
}


void main()
{
   /* Declarations */
   unsigned int16 iRangeMeasurement;
   signed int8 iAngleZ, iAngleX;

      /* Initialize hardware */
      setup_oscillator(OSC_8MHZ,2);
      initStepper();
      initSensors();

      while(TRUE)
      {
         /* Move the motor and recieve motors positions */
         stepperMotorSequence(&iAngleX, &iAngleZ);
         /* Wait for the motor to settle */
         delay_ms(25); // 50 works ok
         /* Read the sensor value */
         iRangeMeasurement = readRangeSensor();
         /* Send the measurements to the PC */
         sendMeasurements(iAngleZ, iAngleX, iRangeMeasurement);
         //printf("%f\n", fRangeMeasurement);
     }
   
}
