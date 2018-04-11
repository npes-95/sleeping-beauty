#include "data_analysis.h"

void Phone::Phone()
{
	// init server connection here
	server = new Server();
	
}

void Phone::run()
{
	// at this point the thread has been started
	running = true;
	
	while(running)
	{
		// poll server every minute and check if anything has changed
		server->read();
		
		alarmTime = server->getAlarmTime();
		alarmSet = server->getAlarmSet();
		
		sleep(60);
		
	}
	
	
}

void Phone::stop()
{
	running = false;
}

void Phone::peakDetected(int signal)
{
	// activate alarm if alarm has been set and we are within half an hour of the set time when a peak has been detected
	
	// get current time
	time_t raw_time = time(NULL);
	tm* current_time = localtime(&raw_time);
	int currentHour = current_time->tm_hour;
	int currentMin = current_time->tm_min;
	
	
	if(alarmTime.tm_hour == currentHour && alarmTime.tm_min > currentMin-30 && alarmSet)
	{
		// do something here
	}
}

