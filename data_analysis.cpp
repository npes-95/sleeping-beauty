#include "data_analysis.h"

DataAnalysis::DataAnalysis(CircularBuffer<int> *adc1_addr, CircularBuffer<int> *adc2_addr, CircularBuffer<int> *adc3_addr, CircularBuffer<int> *adc4_addr, CircularBuffer<int> *accel_addr, int buffer_length, int samp_per)
{
	buflen = buffer_length;
	
	sample_period = samp_per;
	
	adc1_data = adc1_addr;
	adc2_data = adc2_addr;
	adc3_data = adc3_addr;
	adc4_data = adc4_addr;
	accel_data = accel_addr;
	
	cout << "Data Analysis thread initialised" << endl;
	
	
}

void DataAnalysis::run()
{
	
	// at this point the thread has been started
	running = true;
	
	// init peak and mean variables
	float adc1_peak = 0;
	float adc2_peak = 0;
	float adc3_peak = 0;
	float adc4_peak = 0;
	float accel_peak = 0;
	
	float adc1_mean = 0;
	float adc2_mean = 0;
	float adc3_mean = 0;
	float adc4_mean = 0;
	float accel_mean = 0;
	
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
		
		int i = 0;
		
		while(i < buflen/2)
		{
			
			
			if(!adc1_data->empty() && !adc2_data->empty() && !adc3_data->empty() && !adc4_data->empty() && !accel_data->empty())
			{
			
				adc1_temp = (float)adc1_data->get();
				adc2_temp = (float)adc2_data->get();
				adc3_temp = (float)adc3_data->get();
				adc4_temp = (float)adc4_data->get();
				accel_temp = (float)accel_data->get();
			
				// add new data to mean
				adc1_mean += adc1_temp;
				adc2_mean += adc2_temp;
				adc3_mean += adc3_temp;
				adc4_mean += adc4_temp;
				accel_mean += accel_temp;
			
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
		adc1_mean /= buflen/2;
		adc2_mean /= buflen/2;
		adc3_mean /= buflen/2;
		adc4_mean /= buflen/2;
		accel_mean /= buflen/2;
		
		
		// get average peak to mean ratio over all five sensors
		float delta_pmr_mean = (adc1_peak/adc1_mean + adc2_peak/adc2_mean + adc3_peak/adc3_mean + adc4_peak/adc4_mean + accel_peak/accel_mean)/5;
		
		cout << "Average peak to mean ratio: " << delta_pmr_mean << endl;
		
		// if it exceeds certain amount, log as movement, send signal to phone to wake up
		if(delta_pmr_mean>1.1)
		{
			// TO DO: signal construct for bluetooth
			raise(SIGINT);
			
		}	
		
		// reset variables for new window
		adc1_peak = 0;
		adc2_peak = 0;
		adc3_peak = 0;
		adc4_peak = 0;
		accel_peak = 0;
	
		adc1_mean = 0;
		adc2_mean = 0;
		adc3_mean = 0;
		adc4_mean = 0;
		accel_mean = 0;
		
		
	}
	
}

void DataAnalysis::stop()
{
	running = false;
}


void DataAnalysis::connect(void (*callback_func)(int))
{
	// specify a listener function that will be called when the signal is raised (ie: bluetooth thread)
	signal(SIGINT, callback_func);
	
} 

