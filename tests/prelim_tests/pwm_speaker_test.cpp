#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <softPwm.h>

#define SPEAKER_PIN 4

using namespace std;

int main ()
{
	wiringPiSetup () ;
	pinMode (SPEAKER_PIN, OUTPUT) ;
	
	while(true)
	{
		digitalWrite(SPEAKER_PIN, HIGH);
		usleep(800);
		digitalWrite(SPEAKER_PIN, LOW);
		usleep(800);
	}
	
	//softPwmCreate (SPEAKER_PIN, 0, 100) ;
	
	//softPwmWrite (SPEAKER_PIN, 100) ;
	
	/*for(;;)
	{
		delay(1000);
	}*/
	
    
    return 0 ;
}
