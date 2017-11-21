#include <main.h>

#define CHANNEL_LONG_RANGE  5
#define CHANNEL_SHORT_RANGE 6

unsigned int16 readInternalAdc(unsigned int8 channel)
{
  set_adc_channel(channel);
  delay_us(10);

  read_adc(ADC_START_ONLY); // start the ADC for conversion
  
  int1 done = adc_done();   // Poll on ADC result
  while(!done) 
  {
    // wait until measurement is ready
    done = adc_done();
  }
  
  // read conversion result
  return((int16)read_adc(ADC_READ_ONLY))
}

unsigned int16 readLongRangeSensor
{
  unsigned int16 iSensorRead;
  iSensorRead = readInternalAdc(CHANNEL_LONG_RANGE);
  /* Add conversion formulas here */
  return iSensorRead;
}

unsigned int16 readShortRangeSensor
{
  unsigned int16 iSensorRead;
  iSensorRead = readInternalAdc(CHANNEL_SHORT_RANGE);
  /* Add conversion formulas here */
  return iSensorRead;
}

void init()
{
  setup_oscillator(OSC_8MHZ,2);
 
  /* Setup the  ADC to 2.5V */
  setup_vref(VREF_LOW | 0x0C);
  setup_adc(ADC_CLOCK_DIV_32);
	setup_adc_ports (sAN5 | sAN6 | VSS_VREF);
	
  /* Initially start with channel 6 */
  set_adc_channel(6);
}


void main()
{
  init();

  while(1)
  {
    printf("Long range read: %lu\n", readLongRangeSensor());
    printf("Long range read: %lu\n", readShortRangeSensor());
    delay_ms(500);
  }
}