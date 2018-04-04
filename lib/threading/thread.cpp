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
