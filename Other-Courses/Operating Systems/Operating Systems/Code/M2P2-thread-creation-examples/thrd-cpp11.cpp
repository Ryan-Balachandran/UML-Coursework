/**
 * A C++11 thread program illustrating how to
 * create a simple thread and some of the C++11 Thread STL class API.
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 *
 * Most Unix/Linux/OS X users:
 * g++ thrd-cpp11.cpp -lpthread
 */

#include <iostream>
#include <thread>

using namespace std;

int sum; /* this data is shared by the thread(s) */


void runner(int upper)
{
	sum = 0;

	if (upper > 0)
    {
		for (int i = 1; i <= upper; i++)
			sum += i;
	}
}


int main(int argc, char* argv[])
{
	if (argc != 2) {
		cerr << "usage: a.out <integer value>\n";
		return -1;
	}

	int arg = atoi(argv[1]);
	
	if (arg < 0)
    {
		cerr << "Argument " << arg << " must be non-negative\n";
		return -1;
	}

	thread th(&runner, arg);
	th.join();
	cout << "sum = " << sum << endl;
	return 0;
}
