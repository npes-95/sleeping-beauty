#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>

class Server 
{
	// used to store server output
	struct MemoryStruct
	{
		char *memory;
		size_t size;
	};
 
	static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
	
	// instantiate this memory memory to read in json
	struct MemoryStruct json_buf;
	
	// use curl to send html requests to server
	CURL *curl;
	CURLcode res;
	
	// output variables
	bool alarmSet;
	struct tm alarmTime;

    

public:

    Server();
    ~Server();
    void read();
    
    bool getAlarmSet();
    struct tm getAlarmTime();
    
   
};

#endif
