#include <main.h>

struct packet 
{
  unsigned int16 zAngle;
  unsigned int16 yAngle;
  unsigned int16 distance;
};

void sendMeasurements(struct packet * sendPacket)
{
  printf("%lu", sendPacket->zAngle);
}

void init()
{
  setup_oscillator(OSC_8MHZ,2);
}

void main()
{
  init();

  struct packet packetToSend;
  packetToSend.zAngle   = 1234;
  packetToSend.yAngle   = 0xFFFF;
  packetToSend.distance = 0xFFFF;

  sendMeasurements(&packetToSend);

  while(1)
  {
  }
}