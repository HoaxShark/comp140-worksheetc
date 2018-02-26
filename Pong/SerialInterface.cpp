#include "stdafx.h"
#include "SerialInterface.h"
#include <iostream>

using std::cout;
using std::vector;
using std::exception;
using std::stoi;
using std::string;

const bool InStudio = true;
const std::string PORT_NO = "COM4";

SerialInterface::SerialInterface()
{
	if (!InStudio) {
		vector <serial::PortInfo> devicesFound = serial::list_ports(); // checks all serial ports

		vector <serial::PortInfo>::iterator iter = devicesFound.begin(); // 

		while (iter != devicesFound.end()) {
			serial::PortInfo device = *iter++; // gets current device
			string port = device.port.c_str();

			try {
				mySerial = new serial::Serial(port, 115200, serial::Timeout::simpleTimeout(250));

				if (mySerial->isOpen()) {
					cout << "Connection Succes: " << port << "\n";
					connect = true;
					break;
				}
			}
			catch (exception &e) {

			}
		}
	}
	else
	{
		try {
			mySerial = new serial::Serial(PORT_NO, 115200, serial::Timeout::simpleTimeout(250));

			if (mySerial->isOpen()) {
				cout << "Connection Succes: " << PORT_NO << "\n";
				connect = true;
			}
		}
		catch (exception &e) {

		}
	}
}


SerialInterface::~SerialInterface()
{
}

void SerialInterface::send(string msg)
{
	if (connect) {
		mySerial->write(msg); // sends string to serial
	}
}

void SerialInterface::getPositions()
{
	if (connect) {
		mySerial->write("P"); // sends string to get potentiometer readings back

		string result = mySerial->readline();

		if (result.length() >= 9) {
			string sub1 = result.substr(0, 4);
			pot1 = std::stoi(sub1);
			string sub2 = result.substr(5, 9);
			pot2 = std::stoi(sub2);
		}
	}
}

void SerialInterface::lightSwitch(int player)
{
	if (connect && player == 1)
	{
		mySerial->write("L");
	}
	if (connect && player == 2)
	{
		mySerial->write("O");
	}
}

void SerialInterface::close()
{
	mySerial->flush();
	mySerial->close();
}
