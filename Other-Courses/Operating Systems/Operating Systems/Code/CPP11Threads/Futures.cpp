#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <vector>

using namespace std;


int square(int x)
{
    this_thread::sleep_for(chrono::milliseconds(100));
    cout << "x == " << x << ", this_thread::get_id() == " << this_thread::get_id() << endl;
    return x * x;
}


int main()
{
    vector<future<int>> v;
    
    // Create tasks, and obtain promises for future results
    for (int i = 1; i <= 20; i++)
    {
        // see what happens if you substitute launch::deferred
        // <http://www.cplusplus.com/reference/future/async/?kw=async>
        v.push_back(async(launch::deferred, &square, i));
    }
    
    // Redeem the promises of future results, and sum those results
    int sum = 0;
    for (int i = 0; i < 20; i++)
    {
        sum += v[i].get();
    }
    
    cout << "The threads returned the sum == " << sum
         << ". this_thread::get_id() == " << this_thread::get_id() << endl;
    
    return 0;
}
