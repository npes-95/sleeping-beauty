// spi_test.cpp

// tested using MCP3008 ADC 

#include <iostream>
#include <errno.h>
#include <wiringPiSPI.h>
#include <unistd.h>

// channel is the SPI channel that the sensor is connected to on the RPi
// Set this to 0 or 1, depending on how it's connected.
#define SPI_CHANNEL 0

// SPI clock speed
#define CLK_SPEED 1000000

using namespace std;

int main()
{

   int fd, result, adc_out;
   
   // which channel are we using
   int analog_channel = 0;

   // do we want to take the value of the channel or the difference between two channels
   int channel_config = 8;

   // init SPI
   fd = wiringPiSPISetup(SPI_CHANNEL, CLK_SPEED);
   
   cout << "Init result: " << fd << endl;

   sleep(5);

   while(true)
   {

   // need to flush buffer for every new read 

   unsigned char data_buffer[3] = {1};

   // set buffer values: first byte is 1, second is command to retrieve first channel, third doesn't matter

   data_buffer[1] = (analog_channel + channel_config) << 4;




   // get ADC channel values (data command sent using buffer is overwritten by data)

   result = wiringPiSPIDataRW(SPI_CHANNEL, data_buffer, 3);

   // extract 10 bit data from buffer
   adc_out = ((data_buffer[1] & 0x03) << 8) + data_buffer [2];

   // print value
   cout << "Channel 0 data: " << adc_out << endl;

   sleep(2);
   

   
   }
   
}



