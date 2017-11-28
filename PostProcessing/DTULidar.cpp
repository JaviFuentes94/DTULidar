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



using namespace std;

char *portName = "\\\\.\\COM4";

//String for incoming data
char incomingData[MAX_DATA_LENGTH];
char outcommingData[MAX_DATA_LENGTH];

void ReadUsb(SerialPort &serialport) {
	
	while (serialport.isConnected())
	{
		cout << "Write to the device" << endl;
		//cin >> outcommingData;
		//bool writeResult = serialport.writeSerialPort(outcommingData, MAX_DATA_LENGTH);
		int readResult = serialport.readSerialPort(incomingData, MAX_DATA_LENGTH);
		puts(incomingData);
		uint8_t incommingBytes = (uint8_t)incomingData;
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

