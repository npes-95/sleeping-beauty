#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "sensor_data_reader.h"

using namespace std;

int main(int argc, char **argv)
{
	
	// init data buffers
	
	
	// init sensor data collection and analysis threads
	DataIn *sensorDataCollect;
	sensorDataCollect = new DataIn(adc1buf, adc2buf, adc3buf, adc4buf, accelbuf, buflen, sample_period);
	
	// init bluetooth thread
	
	
	
	// start threads here to launch data collection
	sensorDataCollect.start();
	
}
