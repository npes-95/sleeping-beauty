#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "sensor_data_reader.h"
#include "data_analysis.h"
#include "lib/circular_buffer/circular_buffer.h"

#define SAMPLE_RATE 1000 
#define WINDOW_SIZE 5

using namespace std;

int main(int argc, char **argv)
{
	
	// get the sample period in us
	int sample_period = 1/(SAMPLE_RATE*10^-6);
	
	// get buffer length
	int buflen = SAMPLE_RATE*2*WINDOW_SIZE;
	
	// init data buffers (need to be at least twice the window size ~10s)
	CircularBuffer<int> adc1buf(buflen);
	CircularBuffer<int> adc2buf(buflen);
	CircularBuffer<int> adc3buf(buflen);
	CircularBuffer<int> adc4buf(buflen);
	CircularBuffer<int> accelbuf(buflen);
	
	
	// init sensor data collection and analysis threads
	DataIn *sensorDataCollect;
	sensorDataCollect = new DataIn(&adc1buf, &adc2buf, &adc3buf, &adc4buf, &accelbuf, buflen, sample_period);
	
	DataAnalysis *sensorDataAnalyse;
	sensorDataAnalyse = new DataAnalysis(&adc1buf, &adc2buf, &adc3buf, &adc4buf, &accelbuf, buflen, sample_period);
	
	
	// init bluetooth thread
	
	
	
	// start threads here to launch data collection
	sensorDataCollect.start();
	
	// only check data if it is within the time alotted
	
}
