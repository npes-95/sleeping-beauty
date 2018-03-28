#include "thread.h"

void Thread::start()
{
    pthread_create(&thread, NULL, Parallel::staticEntryPoint, this);
}

void * Thread::staticEntryPoint(void * c)
{
    ((Parallel *) c)->entryPoint();
    return NULL;
}

void Thread::entryPoint()
{
    // thread body
    // inherit this class and use it as an easy way to make threads
}
