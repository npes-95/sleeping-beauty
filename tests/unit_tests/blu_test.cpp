#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../interfaces/bluetooth/blucontrol.h"

// compile using:
// g++ -c ../../interfaces/bluetooth/blucontrol.cpp
// g++ -c blu_test.cpp
// g++ blucontrol.o blu_test.o -o blu_test -lbluetooth

using namespace std;

int main(int argc, char **argv)
{
	// test the bluetooth control class: connect to a device, print incoming data
	// everything is initialised when the bluetooth object is created
	BLU phone;
	
	while(true)
	{
		if(phone.dataAvailable())
		{
			cout << "Phone data: " << phone.getData() << endl;
		}
		
	}
	
	
}
