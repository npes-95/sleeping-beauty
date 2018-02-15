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

This file interfaces with the Adafruit LIS3DH breakout board.


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
#include <unistd.h>

#define ACCEL_ADDR 0x18

#define X_REG_LO 0x28
#define X_REG_HI 0x29
#define Y_REG_LO 0x2A
#define Y_REG_HI 0x2B
#define Z_REG_LO 0x2C
#define Z_REG_HI 0x2D

#define WHO_AM_I 0x0F

#define STATUS_REG 0x07

#define CNTRL_REG_1 0x20
#define CNTRL_REG_2 0x21
#define CNTRL_REG_3 0x22
#define CNTRL_REG_4 0x23
#define CNTRL_REG_5 0x24
#define CNTRL_REG_6 0x25

#define INT1_THS 0x32
#define INT1_DUR 0x33
#define INT1_CFG 0x30



using namespace std;

int main()
{
   int fd, x, y, z;

   // Initialize the interface by giving it an external device ID.
   // Could include a shell script here to automatically get it. 
   //
   // It returns a standard file descriptor.
   
   // open device

   fd = wiringPiI2CSetup(ACCEL_ADDR);

   cout << "Init result: "<< fd << endl;

   cout << "Device ID: "<< wiringPiI2CReadReg8(fd, WHO_AM_I) << endl;

   

   // settings/startup sequence

   // enable all axes, set data rate to 10Hz, disable low power mode
   //wiringPiI2CWriteReg8(fd, CNTRL_REG_1, 0x27);

   // filter (disabled)
   //wiringPiI2CWriteReg8(fd, CNTRL_REG_2, 0x00);

   // interrupts (disabled)
   //wiringPiI2CWriteReg8(fd, CNTRL_REG_3, 0x00);

   // resolution, endianess (default LSB), scale selection 
   //wiringPiI2CWriteReg8(fd, CNTRL_REG_4, 0x00); 

   // memory, FIFO, 4D (disabled)
   //wiringPiI2CWriteReg8(fd, CNTRL_REG_5, 0x00); 

   // misc settings
   //wiringPiI2CWriteReg8(fd, CNTRL_REG_5, 0x00); 

   // for interrupt settings write to INT1 registers

  



   sleep(3);

   while(true)
   {

      // check if data is available

      if(wiringPiI2CReadReg8(fd, STATUS_REG) & 0x08)
      {
      

         // get data from accelorometer (read device's registers)

         x = (wiringPiI2CReadReg8(fd, X_REG_HI) << 8) | wiringPiI2CReadReg8(fd, X_REG_LO);
         y = (wiringPiI2CReadReg8(fd, Y_REG_HI) << 8) | wiringPiI2CReadReg8(fd, Y_REG_LO);
         z = (wiringPiI2CReadReg8(fd, Z_REG_HI) << 8) | wiringPiI2CReadReg8(fd, Z_REG_LO);

         // print data

         cout << "X: "<< x << endl; 
         cout << "Y: "<< y << endl; 
         cout << "Z: "<< z << endl; 

      }

      usleep(300000);
 
   }
}