// Resource allocation solution using mutex lock and condition variable

#include <iostream>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <chrono>
#include <vector>

using namespace std;

const bool DEBUG_OUTPUT = false; // set to true for verbose output

const int MAX_RESOURCES = 5;  // number of identical resources, or maximum number of users for a single resource
const int MAX_USERS = 20;     // number of competing threads

// mutex used to allocate the resources
mutex numResources;

// condition variable used to wait for a resource to become available
condition_variable resourceAvailable;

// curResources counts the number of resources available
int curResources = MAX_RESOURCES;

// curCount counts the current number of active threads in critical sections. It should never become greater than MAX_RESOURCES	
int curCount = 0;

// maxCount is updated with the maximum value of curCount as each thread enters its critical section
int maxCount = 0;


/**
 *  Code executed by each thread
 */
void run(int thread_num)
{
    for (int i = 0; i < 1000; i++)
    {
        { // begin critical region for checking that resource is available
            
            unique_lock<mutex> resourceLock(numResources);
            
            resourceAvailable.wait(resourceLock, []{return curResources > 0;}); // wait until resource is available
            
            curResources--;
            curCount++;
            if (maxCount < curCount) maxCount = curCount;
            
            if (DEBUG_OUTPUT)
            {
                cout << "Thread number " << thread_num << " is about to use the resource; curResources == "
                     << curResources << ", curCount == " << curCount << ", maxCount == " << maxCount << endl;
            }
            
            resourceLock.unlock();
            
        }  // end critical region for checking that resource is available
        
        
        /**
         *  This thread can use the resource here.
         */
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); // simulate use of the resource for one msec
        
        
        { // begin critical region for releasing the resource
            
            unique_lock<mutex> resourceLock(numResources);
            
            curCount--;
            curResources++;
            
            if (DEBUG_OUTPUT)
            {
                cout << "Thread number " << thread_num << " has finished using the resource; curResources == "
                     << curResources << ", curCount == " << curCount << ", maxCount == " << maxCount << endl;
            }
            
            resourceAvailable.notify_one(); // signal that resource is available
            
            resourceLock.unlock();
            
        } // end critical region for releasing the resource
        
    } // end for
    
} // end run()


/**
 *  Driver program
 */
int main()
{
    vector<thread> ths;
    
    // Create user threads
    for (int i = 1; i <= MAX_USERS; i++)
    {
        ths.push_back(thread(&run, i));
    }
    
    // Wait for all user threads to complete
    for (auto& th : ths)
    {
        th.join();
    }
    
    cout << "Maximum number of users simultaneously using the resource(s) (should be <= "
         << MAX_RESOURCES << ") was " << maxCount << endl;
    
    return 0;
}
