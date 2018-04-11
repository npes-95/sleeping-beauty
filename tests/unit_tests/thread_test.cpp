#include <stdio.h>
#include <unistd.h>
#include "../../lib/threading/thread.h"

using namespace std;

class TestThread : public Thread
{
	
	public:
		
	TestThread(int _thread_num)
	{
		thread_num = _thread_num;
	}
	
	private:
	
	int thread_num;
	
	// override thread function here
	void run()
	{
		// print thread number
		printf("Thread ID: %i\n", thread_num);
		
	}
};



int main(int argc, char **argv)
{
	TestThread t1(1);
	TestThread t2(2);
	TestThread t3(3);
	
	
	t1.start();
	t2.start();
	t3.start();
	
	t1.join();
	t2.join();
	t3.join();
	
	
	
}
