// Resource allocation solution using Lock with condition object and state variable
import java.util.concurrent.locks.*;

public class ResourceAllocationLockAndCV 
{

	static final int MAX_RESOURCES = 5;  // number of identical resources
	static final int MAX_USERS = 20;     // number of competing threads
	// lock use to start critical section used to allocate the resources
	static ReentrantLock numResources = new ReentrantLock(true);
	// lock used to ensure that the counts are updated under
	// mutual exclusion	
	static ReentrantLock mutexCounts = new ReentrantLock(true);
	// condition object used to wait for a resource to become available
	static Condition resourceAvailable = numResources.newCondition();
	// curResources counts the number of resources available
	static int curResources = MAX_RESOURCES;
	// curCount counts the current number of active threads in critical
	// sections.  It should never get higher than MAX_RESOURCES	
	static int curCount = 0;
	// updated with the maximum value of curCount as each thread enters
	// its critical section.
	static int maxCount = 0;

	static class ResourceUser implements Runnable 
	{

		public void run()
		 {

			for(int i = 0; i < 1000; i++)
			 {

				// comment out try and numResources.lock() to 
				// see what happens without synchronization
				try {
					// take lock to check for availabe resource
					numResources.lock();
					// while zero resources available wait
					while (curResources == 0)
						try {
							// wait to be signalled
							// then recheck condition
							resourceAvailable.await();
						} catch(InterruptedException ie) { }
// beginning of resource use critical section
					try {
						// start critical section for count update
						mutexCounts.lock();
						curResources--;   //  do the decrement of number of resources under
								  //  mutual exclussion also 
						curCount++;
						if(maxCount < curCount)
							maxCount = curCount;
					} finally {
						mutexCounts.unlock();
					}
				// comment out finally block to see what happens
				// without synchronization
				} finally {
					numResources.unlock();
				}

				// use resource

				
				// comment out try and numResources.lock() to 
				// see what happens without synchronization
				try {
					numResources.lock();
					try {
						mutexCounts.lock();
						curCount--;
						curResources++;
						resourceAvailable.signal();
					} finally {
						mutexCounts.unlock();
					}

				// comment out finally block to see what happens
				// without synchronization
				} finally {
					numResources.unlock();
				}
			}
		}
	}

	public static void main(String[] args) {

		Thread[] rusers = new Thread[MAX_USERS];
		for(int i = 0; i < MAX_USERS; i++)
			rusers[i] = new Thread(new ResourceUser());

		for(int i = 0; i < MAX_USERS; i++)
			rusers[i].start();

		for(int i = 0; i < MAX_USERS; i++)
			try {
				rusers[i].join();
			} catch(InterruptedException ie) { }

			
		System.out.println("Maximum active at a time was " + maxCount);
	}
}
