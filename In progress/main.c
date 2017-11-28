#include <main.h>

struct packet_t
{
  unsigned int16 zAngle;
  unsigned int16 yAngle;
  unsigned int16 distance;
};

void sendMeasurements(struct packet_t * sendPacket)
{
   char characterToSend;
   characterToSend = *((char*)&(sendPacket->zAngle));
   putc((int)characterToSend);
   characterToSend = *(((char*)&(sendPacket->zAngle))+1);
   putc((int)characterToSend);
   
   characterToSend = *((char*)&(sendPacket->yAngle));
   putc((int)characterToSend);
   characterToSend = *(((char*)&(sendPacket->yAngle))+1);
   putc((int)characterToSend);
   
   characterToSend = *((char*)&(sendPacket->distance));
   putc((int)characterToSend);
   characterToSend = *(((char*)&(sendPacket->distance))+1);
   putc((int)characterToSend);
   // (sendPacket->zAngle);
   //test2 = 
  //printf("%lu", sendPacket->zAngle);
}

void init()
{
  setup_oscillator(OSC_8MHZ,2);
}

void main()
{
  init();

  struct packet_t packetToSend;
  

  int count = 0;

  while(1)
  {
  packetToSend.zAngle   = 1234+count;
  packetToSend.yAngle   = 5678+count;
  packetToSend.distance = 0xFFFF;
  sendMeasurements(&packetToSend);
  delay_ms(100);
  count++;
  }
}
