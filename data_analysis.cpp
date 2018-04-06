#include "data_analysis.h"

void DataAnalysis::DataAnalysis(CircularBuffer& adc1_addr, CircularBuffer& adc2_addr, CircularBuffer& adc3_addr, CircularBuffer& adc4_addr, CircularBuffer& accel_addr, int buffer_length, int samp_per)
{
	buflen = buffer_length;
	
	sample_period = samp_per;
	
	adc1_data = adc1_addr;
	adc2_data = adc2_addr;
	adc3_data = adc3_addr;
	adc4_data = adc4_addr;
	accel_data = accel_addr;
	
	
	// setup sensors	
	adc = new MCP3008();
	accel = new LIS3DH();
	
}

void DataAnalysis::entryPoint()
{
	// at this point the thread has been started
	running = true;
	
	// init peak and mean variables
	float adc1_window_peak = 0;
	float adc2_window_peak = 0;
	float adc3_window_peak = 0;
	float adc4_window_peak = 0;
	float accel_window_peak = 0;
	
	float adc1_window_mean;
	float adc2_window_mean;
	float adc3_window_mean;
	float adc4_window_mean;
	float accel_window_mean;
	
	// variables to hold the most recent piece of data in
	float adc1_temp;
	float adc2_temp;
	float adc3_temp;
	float adc4_temp;
	float accel_temp;
	
	
	// this is where we want to do stuff
	while(running)
	{
		
		
		// get one window's worth of data
		
		while(int i = 0 < buflen/2)
		{
			while(!adc1_data->empty() && !adc2_data->empty() && !adc3_data->empty() && !adc4_data->empty() && !accel_data->empty())
			{
			
				adc1_temp = (float)adc1_data->get();
				adc2_temp = (float)adc2_data->get();
				adc3_temp = (float)adc3_data->get();
				adc4_temp = (float)adc4_data->get();
				accel_temp = (float)accel_data->get();
			
				// add new data to mean
				adc1_window_mean += adc1_temp;
				adc2_window_mean += adc2_temp;
				adc3_window_mean += adc3_temp;
				adc4_window_mean += adc4_temp;
				accel_window_mean += accel_temp;
			
				// check if new value is bigger than previous
				if(adc1_temp>adc1_peak) adc1_peak = adc1_temp;
				if(adc2_temp>adc2_peak) adc2_peak = adc2_temp;
				if(adc3_temp>adc3_peak) adc3_peak = adc3_temp;
				if(adc4_temp>adc4_peak) adc4_peak = adc4_temp;
				if(accel_temp>accel_peak) accel_peak = accel_temp;
			
			
				i++;
			}
			
		}
		
		// get window mean		
		adc1_window_mean /= buflen/2;
		adc2_window_mean /= buflen/2;
		adc3_window_mean /= buflen/2;
		adc4_window_mean /= buflen/2;
		accel_window_mean /= buflen/2;
		
		
		// get average peak to mean ratio over all five sensors
		float delta_pmr_mean = (adc1_peak/adc1_mean + adc2_peak/adc2_mean + adc3_peak/adc3_mean + adc4_peak/adc4_mean + accel_peak/accel_mean)/5;
		
		// if it exceeds certain amount, log as movement, send signal to phone to wake up
		if(delta_pmr_mean>1.1)
		{
			// TO DO: signal construct for bluetooth
			raise(SIGINT);
			
		}	
		
	}
	
}

void DataAnalysis::stop()
{
	running = false;
}


+void DataAnalysis::connect(void (*callback_func)(int))
+{
+	// specify a listener function that will be called when the signal is raised (ie: bluetooth thread)
+	signal(SIGINT, callback_func);
+	
+} 

