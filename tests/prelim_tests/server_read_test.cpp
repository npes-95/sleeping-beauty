#include <iostream>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>

using namespace std;

struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  mem->memory = (char*)realloc(mem->memory, mem->size + realsize + 1);
  if(mem->memory == NULL) {
    /* out of memory! */ 
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}



int main(void)
{
	
	
  // output variables
  bool alarmSet;
  struct tm alarmTime;
  
  // curl used to fetch data from server 
  CURL *curl;
  CURLcode res;
  curl = curl_easy_init();
  
  
  
  // allocate memory to read in json
  struct MemoryStruct json_buf;
 
  json_buf.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */ 
  json_buf.size = 0;    /* no data at this point */ 
  
  if(curl) {
	 
	 // add auth token to http header 
	struct curl_slist *header = NULL;
	header = curl_slist_append(header, "auth_token:8ad4a3b3-8d28-47ae-87a1-b2c25ffe916d");
	  
	// set header
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
	
	// set address we newed to get data from
    curl_easy_setopt(curl, CURLOPT_URL, "https://sleeping-beauty-api.herokuapp.com/getAlarmInfo");
    
    // set memory write function for curl
    // send all data to this function  */ 
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
	/* we pass our 'jsonbuf' struct to the callback function */ 
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&json_buf);

    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    
    
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

    /* always cleanup */
    curl_easy_cleanup(curl);   
    

    
    
    string output = json_buf.memory;
    
    cout << output.substr(18,19) << endl;
    
    
    // since we know the format of the retuned json, we can easily parse the values
    
    // find whether the alarm has been set
    if(output.find("true") == string::npos)
    {
		alarmSet = false;
		
	} else 
	{
		alarmSet = true;
	}
	
	// parse date and time 
	strptime(output.substr(18,19).c_str(), "%Y-%m-%dT%H:%M:%S", &alarmTime );
	
	
	// check whether we are within half an hour of the set time
	
	time_t raw_time = time(NULL);
	tm* current_time = localtime(&raw_time);
	int currentHour = current_time->tm_hour;
	int currentMin = current_time->tm_min;
	
	if(alarmTime.tm_hour == currentHour && alarmTime.tm_min > currentMin-30)
	{
		cout << "Monitoring sleep movement" << endl;
		
	}
	
	else
	{
		cout << "Not monitoring sleep movement" << endl;
	}
	
	
	cout << "Alarm set: " << alarmSet << endl;
	//cout << "Alarm time: " << alarmTime.tm_hour << " " << alarmTime.tm_min << " " << alarmTime.tm_sec << endl;
	
    
   
    
    
    
    

  }
  return 0;
}
