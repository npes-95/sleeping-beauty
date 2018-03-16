#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../interfaces/accelerometer/LIS3DH.h"

// compile using:
// g++ -c ../../interfaces/accelerometer/LIS3DH.cpp
// g++ -c accelerometer_test.cpp
// g++ LIS3DH.o accelerometer_test.o -o accelerometer_test -lwiringPi

using namespace std;

int main(int argc, char **argv)
{
	// test the accelerometer control class: connect to the, print incoming data regularly
	// everything is initialised when the accelerometer object is created
	LIS3DH accel;
	
	// cancel if sensor isn't connected
	if(accel.getFileDescriptor()<0)
	{
		return 0;		
	}
	
	while(true)
	{
		if(accel.dataAvailable())
		{
			cout << "X value: " << accel.readX() << endl;
			cout << "Y value: " << accel.readY() << endl;
			cout << "Z value: " << accel.readZ() << endl;
			cout << "\n";
		}
		
		
	}
	
	
}
