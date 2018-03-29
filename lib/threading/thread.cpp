#include "thread.h"

void Thread::start()
{
    pthread_create(&thread, NULL, Thread::staticEntryPoint, this);
}

void * Thread::staticEntryPoint(void * c)
{
    ((Thread *) c)->entryPoint();
    return NULL;
}

void Thread::entryPoint()
{
    // thread body
    // inherit this class and override this function
}

void Thread::connect(void (*callback_func)(int))
{
	// specify a listener function that will be called when the signal is raised
	signal(SIGINT, callback_func);
	
} 

void Thread::listenerFunction(int signal)
{
	// user can choose what to do what happens when thread receives a signal
}
