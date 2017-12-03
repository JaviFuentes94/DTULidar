#include <main.h>

#define CHANNEL_LONG_RANGE  4
#define CHANNEL_SHORT_RANGE 6

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
  float fSensorRead;
  float fCumulativeMeasurement = 0.0f;
  
  for(int i = 0; i <5; i++)
  {
     iSensorRead = readInternalAdc(CHANNEL_LONG_RANGE);
  
     if(iSensorRead >= 1000)
     {
      fSensorRead = 0;
      }
      else
     {
         if(iSensorRead <= 573 )
         {
            fSensorRead = 500;
         }
         else
         {
         fSensorRead = 122f / (( 2.5f * ((float) iSensorRead) ) / 1024f - 1.28f);
   //      printf("iSensorRead: %Lu \t in volt: %f \t\t", iSensorRead, (iSensorRead * 2.5f) / 1024f );
       }
     }
     
     fCumulativeMeasurement += fSensorRead; 
   }
  
   return (fCumulativeMeasurement/5.0);
}

float readShortRangeSensor()
{
  unsigned int16 iSensorRead;
  float fSensorRead;
  iSensorRead = readInternalAdc(CHANNEL_SHORT_RANGE);
   // measurement below 30cm
     if(iSensorRead >= 819 ) 
      fSensorRead = 30;
   else 
   {
      // measurement above 150
      if( iSensorRead <= 204 )
         fSensorRead = 150;
      else
         fSensorRead = 50f / (( 2.5f * ((float) iSensorRead) ) / 1024f - 0.1f); 
   }
   
  return fSensorRead;
}

void init()
{
  setup_oscillator(OSC_8MHZ,2);
 
  /* Setup the  ADC to 2.5V */
  //setup_vref(VREF_LOW | 0x0C);
   setup_vref(0xEC);
  setup_adc(ADC_CLOCK_DIV_32);
  setup_adc_ports (sAN4 | sAN6 | VSS_VREF);
   
  /* Initially start with channel 6 */
  set_adc_channel(6);
}


void main()
{
  init();

  while(1)
  {
   printf("Long range read: %f\t", readLongRangeSensor());
   printf("Short range read: %f\n", readShortRangeSensor());    
    
//    printf("Short range read: %lu\n\n", readShortRangeSensor());
    delay_ms(20);
  }
}
