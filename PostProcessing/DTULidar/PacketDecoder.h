#pragma once

#ifndef PACKETDECODER_H
#define PACKETDECODER_H

#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>



namespace PacketDecoder 
{
	struct packet_t {
		uint16_t zAngle;
		uint16_t yAngle;
		uint16_t distance;
	};

	packet_t Decode(char *buffer);
};



#endif
