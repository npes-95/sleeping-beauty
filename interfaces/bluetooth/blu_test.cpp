#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "blucontrol.h"

// compile using:
// g++ -c blucontrol.cpp
// g++ -c blu_test.cpp
// g++ blucontrol.o blu_test.o -o blu_test -lbluetooth

using namespace std;

int main(int argc, char **argv)
{
	// test the bluetooth control class: connect to a device, print incoming data
	// everything is initialised when the bluetooth object is created
	BLU phone;
	
	// output buffer
	char output_buf[1024] = {0};
	memset(output_buf, 0, sizeof(output_buf));
	
	while(true)
	{
		if(phone.dataAvailable())
		{
			phone.getData(output_buf);
			cout << "Phone data: " << output_buf << endl;
			memset(output_buf, 0, sizeof(output_buf));
		}
		
	}
	
	
}
