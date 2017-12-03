#include "stdafx.h"
#include "PacketDecoder.h"

namespace PacketDecoder
{

	int packetSize = 6; //bytes

	packet_t Decode(char *buffer) {

		std::vector<uint16_t> packetVector;
		for (int i = 0; i <= packetSize; i = i + 2)
		{
			uint16_t packetElement = ((uint16_t)buffer[i + 1]<<8) | ((uint16_t)buffer[i] & 0x00FF);
			packetVector.push_back(packetElement);
		}

		packet_t packet;
		packet.zAngle = packetVector.at(0);
		packet.yAngle = packetVector.at(1);
		packet.distance = packetVector.at(2);

		return packet;
	}
}