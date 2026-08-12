// for i in {1..1000}; do ./a.out; done | sort | uniq -c

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <queue>
#include <atomic>
using namespace std;

int main()
{
    int c = 0;
    bool done = false;
    queue<int> goods;
    
    thread producer([&]()
    {
        for (int i = 0; i < 500; ++i)
        {
            goods.push(i);
            c++;
        }
        
        done = true;
    });
    
    thread consumer([&]()
    {
        do
        {
            while (!goods.empty())
            {
                goods.pop();
                c--;
            }
        }
        while (!done);
    });
    
    producer.join();
    consumer.join();
    cout << "Net: " << c << ", size = " << goods.size() << endl;
    // Net and size should be 0 if goods.push() and goods.pop()
    // have correct mutual exclusion & synchronization
}
