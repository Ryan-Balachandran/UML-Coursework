#include <iostream>
#include <vector>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> accum(0);

void square(int x)
{
    int temp = x*x;
    this_thread::sleep_for(std::chrono::milliseconds(1));
    accum += temp;
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
