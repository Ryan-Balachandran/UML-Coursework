#include <iostream>
#include <vector>
#include <thread>

// To see inconsistencies, run multiple times; e.g., in bash:
// 	for i in {1..1000}; do ./a.out; done | sort | uniq -c

using namespace std;

int accum = 0;

void square(int x)
{
    int temp = x * x;
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
