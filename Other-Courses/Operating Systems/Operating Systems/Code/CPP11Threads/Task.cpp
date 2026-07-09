#include <iostream>
#include <future>

using namespace std;


int square(int x)
{
    return x * x;
}


int main()
{
    // promise & future pair: async makes a promise; return type is future<int>
    auto a = async(&square, 10);
    
    // a.get() will wait until promise is fulfilled, and future value is ready
    int v = a.get();
    
    cout << "The thread returned " << v << endl;
    return 0;
}
