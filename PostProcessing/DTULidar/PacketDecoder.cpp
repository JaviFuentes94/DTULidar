#include "stdafx.h"
#include "PacketDecoder.h"

namespace PacketDecoder
{

	packet_t Decode(char *buffer) {

		//std::vector<uint16_t> packetVector;
		packet_t packet;

		float angleConv = 360.0/200.0;

		int8_t zAngleRaw = buffer[0];
		packet.zAngle = (float)zAngleRaw * angleConv;
		
		int8_t xAngleRaw = buffer[1];
		packet.xAngle = (float)xAngleRaw * angleConv;

		//uint16_t packetElement = ((((uint32_t)buffer[i + 1] & 0xFF) << 24) | (((uint32_t)buffer[i + 2] & 0xFF) << 16) | (((uint32_t)buffer[i + 1] & 0xFF) << 8) | ((uint32_t)buffer[i] & 0xFF);
		packet.distance = *((uint16_t*)(&(buffer[2])));
		
		/*char *a = new char[PACKET_SIZE-2];

		for (int i = 2; i < PACKET_SIZE; i++)
		{
			a[i - 2] = buffer[i];
		}

		packet.distance = *((float*)(&(buffer[2])));

		packet.distance = std::atof(a);*/
		
		return packet;
	}

	packet_t Decode(std::vector<char> &buffer) {

		packet_t packet;

		float angleConv = 360.0 / 200.0;

		int8_t zAngleRaw = buffer[0];
		packet.zAngle = (float)zAngleRaw * angleConv;

		int8_t xAngleRaw = buffer[1];
		packet.xAngle = (float)xAngleRaw * angleConv;

		packet.distance = *((uint16_t*)(&(buffer[2])));

		buffer.erase(buffer.begin(),buffer.begin()+PACKET_SIZE);

		return packet;
	}
}