#ifndef PHONE_CONNCTION
#define PHONE_CONNCTION

#include <unistd.h>
#include <time.h>
#include "lib/interfaces/server/server_comms.h"

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
	
	// server ouput values
	struct tm alarmTime;
	bool alarmSet;
	
	Server *server;
	
	
};

#endif
