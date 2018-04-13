#include <iostream>
#include <unistd.h>
#include <wiringPi.h>

#define BUTTON_PIN 0

using namespace std;

int main ()
{
	wiringPiSetup () ;
	pinMode (BUTTON_PIN, INPUT) ;
	
	bool buttonPressed;
	
	while (true)
	{
		usleep(500);
		buttonPressed = (bool)digitalRead (BUTTON_PIN);
		
		if(buttonPressed)
		{
			cout << "Button pressed!" << endl;
		}
		
		 
    }
    
    return 0 ;
}
