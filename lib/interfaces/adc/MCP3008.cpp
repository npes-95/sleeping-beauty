#include <iostream>
#include <errno.h>
#include <wiringPiSPI.h>
#include <unistd.h>
#include "MCP3008.h"

using namespace std;


MCP3008::MCP3008(int spi_channel, int clk_speed)
{
	// spi_channel is the SPI channel that the sensor is connected to on the RPi
	// Set this to 0 or 1, depending on how it's connected.
	// clk_speed is the SPI clock speed
	// erroneous values are handled by the wiringPi library

	// init SPI
	fd = wiringPiSPISetup(spi_channel, clk_speed);

	if(fd<0)
	{
		cout << "Initialisation error, the device could not be opened (errno: " << fd << ")." << endl;
	} else
	{
		cout << "Initialisation successful! Device number: " << fd << endl;
	}

}

int MCP3008::getFileDescriptor()
{
	// use this to check if initialisation has been successful
	return fd;
}

int MCP3008::readChannel(int analog_channel, int channel_config)
{

	if(analog_channel<0 || analog_channel>7)
	{
		cout << "This device only has 8 channels, numbered 0-7." << endl;
		return -1;
	}

	// need to flush buffer for every new read 
   	unsigned char data_buffer[3] = {1};

   	// set buffer values: first byte is 1, second is command to retrieve first channel, third doesn't matter
	data_buffer[1] = (analog_channel + channel_config) << 4;

	// get ADC channel value (data command sent using buffer is overwritten by data)
    int result = wiringPiSPIDataRW(spi_channel, data_buffer, 3);

    // extract 10 bit data from buffer and return
    return ((data_buffer[1] & 0x03) << 8) + data_buffer [2];
}
