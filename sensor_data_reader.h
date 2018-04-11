#ifndef SENSOR_DATA_READER
#define SENSOR_DATA_READER

#include <csignal>
#include <unistd.h>
#include "lib/threading/thread.h"
#include "lib/interfaces/accelerometer/LIS3DH.h"
#include "lib/interfaces/adc/MCP3008.h"
#include "lib/circular_buffer/circular_buffer.h"

class DataIn : public Thread
{
public:

	DataIn(CircularBuffer& adc1_addr, CircularBuffer& adc2_addr, CircularBuffer& adc3_addr, CircularBuffer& adc4_addr, CircularBuffer& accel_addr, int buffer_length, int samp_per);
	void stop();
	
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
	
	// adc (with pressure sensors connected)
	MCP3008 *adc;
	
	// accelerometer
	LIS3DH *accel;
	
	// status
	bool running;
	
	// override thread function here
	void run();
	
};

#endif
