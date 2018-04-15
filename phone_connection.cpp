#include "phone_connection.h"

Phone::Phone()
{
	// init server connection here
	server = new Server();
	
	// get alarm data from server to reset static variables
	server->read();
	alarmTime = server->getAlarmTime();
	alarmSet = server->getAlarmSet();
	
	cout << "Connection to server established." << endl;
	
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
	
	cout << "Peak detected, signal received." << endl;
	
	// get current time
	time_t raw_time = time(NULL);
	tm* current_time = localtime(&raw_time);
	int currentHour = current_time->tm_hour;
	int currentMin = current_time->tm_min;
	
	
	if(alarmTime.tm_hour == currentHour && alarmTime.tm_min > currentMin-30 && alarmSet)
	{
		// activate alarm
		
		int buttonPin = 5;
		int speakerPin = 4;
		
		// setup pin connections
		wiringPiSetup();	
		pinMode(buttonPin, INPUT);
		pinMode(speakerPin, OUTPUT);
		
			// emit alarm tone until button has been pressed
		while(!buttonPressed)
		{
			digitalWrite(speakerPin, HIGH);
			usleep(800);
			digitalWrite(4, LOW);
			usleep(800);
			buttonPressed = (bool)digitalRead(buttonPin);
		}
	}
}

// define the static variables
bool Phone::alarmSet;
struct tm Phone::alarmTime;

