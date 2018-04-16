// test server class
#include <time.h>
#include "../../lib/interfaces/server/server_comms.h"

using namespace std;


int main(int argc, char **argv)
{
	Server phone;
	
	phone.read();
	
	cout << "Alarm active: " << phone.getAlarmSet() << endl;;
	
	struct tm alarmTime = phone.getAlarmTime();
	
	cout << "Alarm set to ring at: " << alarmTime.tm_hour << ":" << alarmTime.tm_min << endl;0
}
