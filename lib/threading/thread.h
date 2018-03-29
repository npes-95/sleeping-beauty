// using: https://stackoverflow.com/questions/13205446/how-to-create-a-thread-inside-a-class-function

#ifndef THREAD_H
#define THREAD_H

#include <pthread.h>

using namespace std;

class Thread
{
private:
    pthread_t thread;

    static void * staticEntryPoint(void * c);
    void entryPoint();
    void listenerFunction(int signal);


public:
    void start();
    void connect(void (*callback_func)(int));
    void (*getListener())(int)
	{
		return Thread::listenerFunction
	};
    
};


#endif
