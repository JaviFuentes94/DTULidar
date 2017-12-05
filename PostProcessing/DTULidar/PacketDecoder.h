#pragma once

#ifndef PACKETDECODER_H
#define PACKETDECODER_H
#define PACKET_SIZE 4

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>



namespace PacketDecoder 
{
	struct packet_t {
		float  zAngle;
		float  xAngle;
		uint16_t distance;
	};

	packet_t Decode(char *buffer);
};



#endif
