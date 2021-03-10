#include <iostream>
#include <thread>
#include <mutex>
#include <omp.h>
#include <math.h>

using namespace std;
mutex my_mutex;

void threadFunction()
{
	
	my_mutex.lock();
	for (int i = 0; i < 10000; sin(i))
	{

	}

	cout << "тред пришёл, его ID: " << this_thread::get_id<< endl;

	cout << "тред ушёл, его ID: " << this_thread::get_id << endl;

	my_mutex.unlock();
}


int main()
{
	setlocale(LC_ALL, "RUS");

	thread one(threadFunction);
	thread two(threadFunction);

	one.join();
	two.join();

	return 0;
}