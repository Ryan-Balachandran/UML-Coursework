#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

int accum = 0;
mutex accum_mutex;

void square(int x)
{
	int temp = x * x;
	this_thread::sleep_for(std::chrono::milliseconds(1));
	accum_mutex.lock(); // begin critical region
	accum += temp;
	accum_mutex.unlock(); // end critical region
}

int main()
{
	vector<thread> ths;
	for (int i = 1; i <= 20; i++)
    {
		ths.push_back(thread(&square, i));
	}

	for (auto& th : ths)
    {
		th.join();
	}
    
	cout << "accum = " << accum << endl;
	return 0;
}
