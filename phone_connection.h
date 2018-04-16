#ifndef PHONE_CONNCTION
#define PHONE_CONNCTION

#include <iostream>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include "lib/threading/thread.h"
#include "lib/interfaces/server/server_comms.h"

using namespace std;

class Phone : public Thread 
{
public:

	Phone();
	void stop();
	static void peakDetected(int signal);
	static struct tm alarmTime;
	static bool alarmSet;
	
private:	
	
	// status
	bool running;
	
	// override thread function here
	void run();
	

	
	Server *server;
	
	
};

#endif
