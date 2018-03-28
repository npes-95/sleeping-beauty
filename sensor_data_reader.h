#ifndef SENSOR_DATA_READER
#define SENSOR_DATA_READER

#include <unistd.h>
#include "lib/threading/thread.h"
#include "lib/interfaces/accelerometer/LIS3DH.h"
#include "lib/interfaces/adc/MCP3008.h"

class DataIn : public Thread
{
public:

	DataIn(int adc1_addr, int adc2_addr, int adc3_addr, int adc4_addr, int accel_addr, int buffer_length, int samp_per);
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
	
	// adc (with pressure sensors connected)
	MCP3008 *adc;
	
	// accelerometer
	LIS3DH *accel;
	
	// status
	bool running;
	
	// override thread function here
	void entryPoint() override;
};

#endif
