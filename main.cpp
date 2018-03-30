#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "sensor_data_reader.h"
#include "data_analysis.h"

using namespace std;

int main(int argc, char **argv)
{
	
	// init data buffers (need to be at least twice the window size ~10s)
	
	
	// init sensor data collection and analysis threads
	DataIn *sensorDataCollect;
	sensorDataCollect = new DataIn(adc1buf, adc2buf, adc3buf, adc4buf, accelbuf, buflen, sample_period);
	
	DataAnalysis *sensorDataAnalyse;
	sensorDataAnalyse = new DataAnalysis(adc1buf, adc2buf, adc3buf, adc4buf, accelbuf, buflen, sample_period);
	
	// pass semaphore to threads so they are synchronised
	static sem_t dataAvailable;
	sem_init(&dataAvailable,0,0);
	
	sensorDataCollect.sync(dataAvailable);
	sensorDataAnalyse.sync(dataAvailable);
	
	
	// init bluetooth thread
	
	
	
	// start threads here to launch data collection
	sensorDataCollect.start();
	
	// only check data if it is within the time alotted
	
}