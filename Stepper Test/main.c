
#include <main.h>
#include "lib/stepperControl.c"



////////////////////////////////////////////////////////////////////
/*

#define CHANNEL_LONG_RANGE  4
#define CHANNEL_SHORT_RANGE 6

float rescaleLongRangeSensor(unsigned int16 adcValue)
{
  float rescaledValue = 0.0;
  
  if(adcValue >= 1000)
  {
      rescaledValue = 0.0;
  }
  else if(adcValue <= 573)
  {
      rescaledValue = 5.0;
  }
  else
  {
      rescaledValue = 122.0f / (( 2.5f * ((float) adcValue) ) / 1024f - 1.28f);
  }  
  return rescaledValue;
}

unsigned int16 readInternalAdc(unsigned int8 channel)
{
  set_adc_channel(channel);
  delay_us(20);

  read_adc(ADC_START_ONLY); // start the ADC for conversion
  
  int1 done = adc_done();   // Poll on ADC result
  while(!done) 
  {
    // wait until measurement is ready
    done = adc_done();
  }
  
  // read conversion result
  return((int16)read_adc(ADC_READ_ONLY));
}

//unsigned int16 readLongRangeSensor()
float readLongRangeSensor()
{
  unsigned int16 iSensorRead;
  float rescaledValue;
  iSensorRead = readInternalAdc(CHANNEL_LONG_RANGE);
  rescaledValue = rescaleLongRangeSensor(iSensorRead);
  printf("Original value: %Lu   Rescaled value: %f\n", iSensorRead, rescaledValue);
  return rescaledValue;
}

unsigned int16 readShortRangeSensor()
{
  unsigned int16 iSensorRead;
  iSensorRead = readInternalAdc(CHANNEL_SHORT_RANGE);
  /* Add conversion formulas here 
  return iSensorRead;
}

*/

/*
void init()
{
//  setup_oscillator(OSC_8MHZ,2);
 
  // Setup the  ADC to 2.5V 
  //setup_vref(VREF_LOW | 0x0C);
   setup_vref(0xEC);
  setup_adc(ADC_CLOCK_DIV_32);
  setup_adc_ports (sAN4 | sAN6 | VSS_VREF);
   
  //Initially start with channel 6 
  set_adc_channel(6);
}
*/


////////////////////////////////////////////////////////////////////

/*
void initStepper()
{
   set_tris_c(0xF0);
}


void stepperRotateSingleRight()
{
     iCurrentPosition = ((iCurrentPosition+1)&3);
     
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

*/


void readLongRangeSensor()
{
}

void main()
{
   setup_oscillator(OSC_8MHZ,2);
   initStepper();
   while(TRUE)
   {
      stepperRotateSingleRight(1);
      delay_ms(500);
      
   }
}
