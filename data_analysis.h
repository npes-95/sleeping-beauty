#ifndef DATA_ANALYSIS
#define DATA_ANALYSIS

#include <unistd.h>
#include "lib/threading/thread.h"

class DataAnalysis : public Thread
{
public:

	DataAnalysis(int adc1_addr, int adc2_addr, int adc3_addr, int adc4_addr, int accel_addr, int buffer_length, int samp_per);
	void stop();
	
private:	

	// addresses for data buffers
	int adc1_data;
	int adc2_data;
	int adc3_data;
	int adc4_data;
	int accel_data;
	
	// buffer length
	int buflen;
	
	// sample period (defined by how fast analysis thread can process data)
	int sample_period;
	
	// status
	bool running;
	
	// see if data is available
	bool dataAvailable;
	
	// override thread function here
	void entryPoint() override;
	
	// callback function for servicing the incoming data available signal
	void listenerFunction() override;
	
	
};

#endif
