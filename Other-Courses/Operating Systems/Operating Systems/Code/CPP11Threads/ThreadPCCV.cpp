// for i in {1..1000}; do ./a.out; done | sort | uniq -c

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <queue>

using namespace std;

condition_variable cond_var;
mutex m;

int main()
{
    int c = 0;
    bool notified = false;
    bool done = false;
    queue<int> goods;
    
    thread producer([&]()
    {
        
        for (int i = 1; i <= 500; ++i)
        {
            lock_guard<mutex> lk(m); // begin critical region
            
            goods.push(i);
            c++;
            notified = true;
            if (i == 500) done = true;
            cond_var.notify_one();
            
        } // end critical region (lk goes out of scope)
    });
    
    thread consumer([&]()
    {
        
        do
        {
            unique_lock<mutex> lock(m); // begin critical region
            
            while (!notified)
                cond_var.wait(lock);
            
            while (!goods.empty())
            {
                goods.pop();
                c--;
            }
            
            notified = false;
            
            lock.unlock(); // end critical region
            
        }
        while (!done || notified);
    });
    
    producer.join();
    consumer.join();
    cout << "Net: " << c << ", size: " << goods.size() << endl;
    // Net and size should be 0 if goods.push() and goods.pop()
    // have correct mutual exclusion & synchronization
}
