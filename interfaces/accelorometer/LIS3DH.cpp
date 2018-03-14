#include <iostream>
#include <errno.h>
#include <wiringPiI2C.h>
#include <unistd.h>
#include "LIS3DH.h"

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


LIS3DH::LIS3DH()
{
	// init I2C
	fd = wiringPiI2CSetup(ACCEL_ADDR);

	if(fd<0)
	{
		cout << "Initialisation error, the device could not be opened (errno: " << fd << ")." << endl;
	} else
	{
		cout << "Initialisation successful! Device number: " << fd << endl;
	}

}

LIS3DH::getFileDescriptor()
{
	// use this to check if initialisation has been successful
	return fd;
}

LIS3DH::dataAvailable()
{
	// checks is data available in XYZ registers
	return iringPiI2CReadReg8(fd, STATUS_REG) & 0x08;
}

LIS3DH::readX()
{
	return (wiringPiI2CReadReg8(fd, X_REG_HI) << 8) | wiringPiI2CReadReg8(fd, X_REG_LO);
}

LIS3DH::readY()
{
	return (wiringPiI2CReadReg8(fd, Y_REG_HI) << 8) | wiringPiI2CReadReg8(fd, Y_REG_LO);
}

LIS3DH::readZ()
{
	return (wiringPiI2CReadReg8(fd, Z_REG_HI) << 8) | wiringPiI2CReadReg8(fd, Z_REG_LO);
}


