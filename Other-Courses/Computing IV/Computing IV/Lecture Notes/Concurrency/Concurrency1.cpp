#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

//------- how to define -----------//
void hello()
{
    std::cout << "Hello Concurrent World\n Inside thread\n"<<
    std::this_thread::get_id()<<std::endl;
    std::cout << std::endl;
}

//------- Sharing problem -----------//
class Counter
{
private:
    
public:
    int value;
    Counter():value(0){}
    void increment() { ++value; }
    //added later to show lock_guard
    void decrement()
    {
        if (value == 0)
        {
            throw "Value cannot be less than 0";
        }
        
        --value;
    }
};

class Counter1
{
public:
    std::mutex mutex;
    int value;
    Counter1() :value(0) {}
    void increment() { mutex.lock(); ++value; mutex.unlock(); }
};

struct ConcurrentCounter
{
    std::mutex mutex;
    Counter counter;
    
    void increment()
    {
        mutex.lock();
        counter.increment();
        mutex.unlock();
    }
    
    void decrement()
    {
        mutex.lock();        //mutex.lock() is called when the instance of
        //std::lock_guard is constructed
        counter.decrement(); //mutex.unlock() is called when
        // the instance guard is descontructed
        mutex.unlock();
    }
};
int main()
{
    std::thread t(hello);
    std::cout << "----- Outside thread" << std::endl;
    std::thread tt(hello);
    std::cout << "----- Outside thread" << std::endl;
    t.join();
    tt.join();
    
    //------- Sharing problem -----------//
    Counter count;
    std::vector<std::thread> threads;
    for (int i = 0; i < 5; ++i)
    {
        threads.push_back(std::thread([&count]()
        {
            for (int i = 0; i < 5000; ++i)
                count.increment();
            
        }));
    }
    
    std::cout << count.value << std::endl;
    for (auto & thread : threads)
        thread.join();
    
    std::cout << count.value << std::endl;    // 23292
    // 24070
    // 21619
    std::cout << "----------------Counter1-------------\n";
    Counter count1;
    std::vector<std::thread> threads1;
    
    for (int i = 0; i < 5; ++i)
    {
        threads1.push_back(std::thread([&count1]()
        {
            for (int i = 0; i < 5; ++i)
                count1.increment();
            
        }));
    }
    
    std::cout << count.value << std::endl;
    /*for (auto & thread : threads1)
     for (int i = 0; i < 6; ++i)
     count1.decrement();*/
    
    for (auto & thread : threads1)
        thread.join();
    std::cout << count.value << std::endl;  //24063
    return 0;
}

