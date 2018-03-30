#include "sensor_data_reader.h"

void DataIn::DataIn(int adc1_addr, int adc2_addr, int adc3_addr, int adc4_addr, int accel_addr, int buffer_length, int samp_per)
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

void DataIn::entryPoint()
{
	// at this point the thread has been started
	running = true;
	
	// this is where we want to do stuff
	while(running)
	{
		// get data and place in buffer at sample freq
		while(int i = 0 < buflen)
		{
			adc1_data[i] = adc->readChannel(0);
			adc2_data[i] = adc->readChannel(1);
			adc3_data[i] = adc->readChannel(2);
			adc4_data[i] = adc->readChannel(3);
			accel_data[i] = accel->readX();
			
			usleep(sample_period);		
		}
		
		
		// when buffer is full, send signal to analysis thread to say that the data is available
		sem_post(&signal);
	}
	
}

void DataIn::stop()
{
	running = false;
}


