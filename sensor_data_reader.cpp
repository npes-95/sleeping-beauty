#include "sensor_data_reader.h"

void DataIn::DataIn(CircularBuffer& adc1_addr, CircularBuffer& adc2_addr, CircularBuffer& adc3_addr, CircularBuffer& adc4_addr, CircularBuffer& accel_addr, int buffer_length, int samp_per)
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

void DataIn::run()
{
	// at this point the thread has been started
	running = true;
	
	// this is where we want to do stuff
	while(running)
	{
		// while there is space in the buffer get data and place in buffer at sample freq
		while(!adc1_data->full() && !adc2_data->full() && !adc3_data->full() && !adc4_data->full() && !accel_data->full())
		{
			adc1_data->put(adc->readChannel(0));
			adc2_data->put(adc->readChannel(1));
			adc3_data->put(adc->readChannel(2));
			adc4_data->put(adc->readChannel(3));
			accel_data->put(accel->readX());
			
			usleep(sample_period);		
		}
		
		// if this point is reached, the analysis function isn't fast enough to cope with the incoming data rate
		// signal error
		cout << "\n\nBuffer overflow!\n\n";
		
		
		
	}
	
}

void DataIn::stop()
{
	running = false;
}


