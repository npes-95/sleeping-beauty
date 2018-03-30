#include "data_analysis.h"

void DataAnalysis::DataAnalysis(int adc1_addr, int adc2_addr, int adc3_addr, int adc4_addr, int accel_addr, int buffer_length, int samp_per)
{
	adc1_data = adc1_addr;
	adc2_data = adc2_addr;
	adc3_data = adc3_addr;
	adc4_data = adc4_addr;
	accel_data = accel_addr;
	
	buflen = buffer_length;
	
	sample_period = samp_per;
	
	
	// setup sensors	
	adc = new MCP3008();
	accel = new LIS3DH();
	
}

void DataAnalysis::entryPoint()
{
	// at this point the thread has been started
	running = true;
	
	// data not available
	dataAvailable = false;
	
	// this is where we want to do stuff
	while(running)
	{
		// wait for collect thread to send signal indicating data is ready
		sem_wait(&signal)
		// copy data into internal class memory
		
		// run peak to mean ratio over window
		
		// if it exceeds certain amount, log as movement, send signal to phone to wake up
	
		// TO DO: signal constructs
	}
	
}

void DataAnalysis::stop()
{
	running = false;
}

