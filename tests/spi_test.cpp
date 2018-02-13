// spi_test.cpp

#include <iostream>
#include <errno.h>
#include <wiringPiSPI.h>
#include <unistd.h>

// channel is the wiringPi name for the chip select (or chip enable) pin.
// Set this to 0 or 1, depending on how it's connected.
#define CS 1

// SPI clock speed
#define CLK_SPEED 500000

using namespace std;

int main()
{

   int fd, result;
   unsigned char data_buffer[100];

   // init SPI
   fd = wiringPiSPISetup(CS, CLK_SPEED);

   while(true)
   {

   // get ADC channel values

   result = wiringPiSPIDataRW(CS, buffer, 2);

   // print

   
   }
   
}



