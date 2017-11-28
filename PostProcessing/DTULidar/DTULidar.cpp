// DTULidar.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread> 
#include <cstdio>

#include "SerialPort.h"
#include "PacketDecoder.h"


using namespace std;

char *portName = "\\\\.\\COM8";

//String for incoming data
char incomingData[MAX_DATA_LENGTH];
char outcommingData[MAX_DATA_LENGTH];
int readAngle;
void ReadUsb(SerialPort &serialport) {
	
	while (serialport.isConnected())
	{
		int bytesRead = serialport.readSerialPort(incomingData, MAX_DATA_LENGTH);

		//puts(incomingData);
		if (bytesRead >= 6) {
			//sscanf_s(incomingData, "%d", &readAngle);
			//printf("%d\n", readAngle);
			PacketDecoder::packet_t packet = PacketDecoder::Decode(incomingData);
			printf("zAngle: %d \n", packet.zAngle);
			printf("yAngle: %d \n", packet.yAngle);
			printf("Distance: %d \n", packet.distance);
		}
		Sleep(100);
	}
}

int main()
{
	SerialPort serialport(portName);
	if (serialport.isConnected()) cout << "Connected" << endl;
	else cout << "Error. Couldn't connect to device";

	thread usbThread(ReadUsb, serialport);
	usbThread.join();

	getchar();
	return 0;
}

