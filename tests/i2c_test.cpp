/******************************************************************************
i2c_test.cpp

BASED ON:

Raspberry Pi I2C interface demo
Byron Jacquot @ SparkFun Electronics>
4/2/2014
https://github.com/sparkfun/Pi_Wedge

A brief demonstration of the Raspberry Pi I2C interface

Resources:

This example makes use of the Wiring Pi library, which streamlines the interface
the the I/O pins on the Raspberry Pi, providing an API that is similar to the
Arduino.  You can learn about installing Wiring Pi here:
http://wiringpi.com/download-and-install/

The I2C API is documented here:
https://projects.drogon.net/raspberry-pi/wiringpi/i2c-library/

The init call returns a standard file descriptor.  More detailed configuration
of the interface can be performed using ioctl calls on that descriptor.
See the wiringPi I2C implementation (wiringPi/wiringPiI2C.c) for some examples.
Parameters configurable with ioctl are documented here:
http://git.kernel.org/cgit/linux/kernel/git/torvalds/linux.git/tree/Documentation/i2c/dev-interface

Hardware connections:

This file interfaces with the Adafruit LIS3DH breakout board:
https://www.sparkfun.com/products/8736


To build this file, I use the command:
>  g++ i2c_test.cpp -lwiringPi

Then to run it, first the I2C kernel module needs to be loaded.  This can be 
done using the GPIO utility.
> gpio load i2c 400
> ./a.out


Development environment specifics:
Tested on Raspberry Pi V3 hardware, running Raspbian.
Building with GCC 6.3.0 20170516 (Raspbian 6.3.0-18+rpi1)

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#include <iostream>
#include <errno.h>
#include <wiringPiI2C.h>

using namespace std;

int main()
{
   int fd, result;

   // Initialize the interface by giving it an external device ID.
   // The defaults to address 0x60.   
   //
   // It returns a standard file descriptor.
   // 
   fd = wiringPiI2CSetup(0x60);

   cout << "Init result: "<< fd << endl;

   for(int i = 0; i < 0x0000ffff; i++)
   {
      // I tried using the "fast write" command, but couldn't get it to work.  
      // It's not entirely obvious what's happening behind the scenes as
      // regards to endianness or length of data sent.  I think it's only 
      // sending one byte, when we really need two.
      //
      // So instead I'm doing a 16 bit register access.  It appears to 
      // properly handle the endianness, and the length is specified by the 
      // call.  The only question was the register address, which is the 
      // concatenation of the command (010x = write DAC output) 
      // and power down (x00x = power up) bits.
      result = wiringPiI2CWriteReg16(fd, 0x40, (i & 0xfff) );

      if(result == -1)
      {
         cout << "Error.  Errno is: " << errno << endl;
      }
   }
}