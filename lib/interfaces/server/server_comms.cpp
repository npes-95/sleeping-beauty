#include "server_comms.h"

using namespace std;


Server::Server()
{
	// init json buffer
	json_buf.memory = (char*)malloc(1);  /* will be grown as needed by the realloc above */ 
	json_buf.size = 0;    /* no data at this point */ 
  
	
	// init curl
	curl = curl_easy_init();
	
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
	
	
	
}

Server::~Server()
{
	curl_easy_cleanup(curl);  
}

void Server::read()
{
	// read from server
	res = curl_easy_perform(curl);
    
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
              
    // parse json in buffer
    string output = json_buf.memory;
    
    // find whether the alarm has been set
    if(output.find("true") == string::npos)
    {
		alarmSet = false;
		
	} else 
	{
		alarmSet = true;
	}
	
	// parse date & time alarm has been set to
	strptime(output.substr(18,19).c_str(), "%Y-%m-%dT%H:%M:%S", &alarmTime );
     
}

bool Server::getAlarmSet()
{
	return alarmSet;
}

struct tm Server::getAlarmTime()
{
	return alarmTime;
}



size_t Server::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
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
