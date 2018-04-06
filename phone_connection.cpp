#include "data_analysis.h"

void Phone::Phone()
{
	// init bluetooth connection here
	
}

void Phone::entryPoint()
{
	// at this point the thread has been started
	running = true;
	
	while(running)
	{
		// wait for phone messages
	}
	
	
}

void Phone::stop()
{
	running = false;
}

void Phone::peakDetected(int signal)
{
	// send message to phone over bluetooth that peak has been detected
}

