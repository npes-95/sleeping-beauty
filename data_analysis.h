#ifndef DATA_ANALYSIS
#define DATA_ANALYSIS

#include <unistd.h>
#include <csignal>
#include "lib/threading/thread.h"
#include "lib/circular_buffer/circular_buffer.h"

class DataAnalysis : public Thread
{
public:

	DataAnalysis(CircularBuffer& adc1_addr, CircularBuffer& adc2_addr, CircularBuffer& adc3_addr, CircularBuffer& adc4_addr, CircularBuffer& accel_addr, int buffer_length, int samp_per);
	void stop();
	void connect(void (*callback_func)(int));
	
private:	

	// addresses for data buffers
	CircularBuffer& adc1_data;
	CircularBuffer& adc2_data;
	CircularBuffer& adc3_data;
	CircularBuffer& adc4_data;
	CircularBuffer& accel_data;
	
	
	// buffer length
	int buflen;
	
	// sample period (defined by how fast analysis thread can process data)
	int sample_period;
	
	// status
	bool running;
	
	// override thread function here
	void entryPoint() override;
	
	
};

#endif
