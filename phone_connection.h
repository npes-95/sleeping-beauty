#ifndef PHONE_CONNCTION
#define PHONE_CONNCTION

#include <unistd.h>

class Phone : public Thread
{
public:

	Phone();
	void stop();
	void peakDetected(int signal)
	
private:	
	
	// status
	bool running;
	
	// override thread function here
	void entryPoint() override;
	
	
};

#endif
