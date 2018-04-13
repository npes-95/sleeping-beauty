#ifndef DATA_ANALYSIS
#define DATA_ANALYSIS

#include <unistd.h>
#include <csignal>
#include <iostream>
#include "lib/threading/thread.h"
#include "lib/circular_buffer/circular_buffer.h"

using namespace std;

class DataAnalysis : public Thread
{
public:

	DataAnalysis(CircularBuffer<int> *adc1_addr, CircularBuffer<int> *adc2_addr, CircularBuffer<int> *adc3_addr, CircularBuffer<int> *adc4_addr, CircularBuffer<int> *accel_addr, int buffer_length, int samp_per);
	void stop();
	void connect(void (*callback_func)(int));
	
private:	

	// addresses for data buffers
	CircularBuffer<int> *adc1_data;
	CircularBuffer<int> *adc2_data;
	CircularBuffer<int> *adc3_data;
	CircularBuffer<int> *adc4_data;
	CircularBuffer<int> *accel_data;
	
	
	// buffer length
	int buflen;
	
	// sample period (defined by how fast analysis thread can process data)
	int sample_period;
	
	// status
	bool running;
	
	// override thread function here
	void run();
	
	
};

#endif
