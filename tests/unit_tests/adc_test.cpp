#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../interfaces/adc/MCP3008.h"

// compile using:
// g++ -c ../../interfaces/adc/MCP3008.cpp
// g++ -c adc_test.cpp
// g++ MCP3008.o adc_test.o -o adc_test -lwiringPi

using namespace std;

int main(int argc, char **argv)
{
	// test the ADC control class: connect to the, print incoming data regularly
	// everything is initialised when the ADC object is created
	// default channel is 0, default clock speed is 1MHz
	MCP3008 adc;
	
	// cancel if ADC isn't connected
	if(adc.getFileDescriptor()<0)
	{
		return 0;		
	}
	
	while(true)
	{
		for(int channel = 0; channel<8; channel++)
		{
			cout << "Channel " << channel << "value: " << adc.readChannel(channel) << endl;
		}
		
		cout << "\n";
		sleep(2);
		
	}
	
	
}
