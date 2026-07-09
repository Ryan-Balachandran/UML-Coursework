//  Using a counting semaphore to allowed identical resources to competing 
//  threads.   Counts are used to demonstrate that only MAX_RESOURCES threads
//  are active in the critical section at a time.
import java.util.concurrent.*;

public class ResourceAllocation 
{

	static final int MAX_RESOURCES = 5;  // number of identical resources
	static final int MAX_USERS = 20;     // number of competing threads
	// counting semaphore used to allocate the resources
	static Semaphore numResources = new Semaphore(MAX_RESOURCES, true);
	// binary semaphore used to ensure that the counts are updated under
	// mutual exclusion
	static Semaphore mutexCounts = new Semaphore(1, true);
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
				// acquire the counting semaphore to use
				// one of the resources
				// only MAX_REOSOURCES threads get through
				// at a time
				// comment out try block to see what
				// happens without synchronization
				try 
				{
					numResources.acquire();
				} catch(InterruptedException ie) { }
				  
//  beginning of resource use critical section

				// acquire binary semaphore to update counts
				// under mutual exclusion
				// critical section for count variable update
				try 
				{
					mutexCounts.acquire();
				} catch(InterruptedException ie) { }
				
				curCount++;  // another active process
				// update maxCount if new maximum active 
				// is reached
				if(maxCount < curCount)
					maxCount = curCount;
				mutexCounts.release();  // leaving critical
							// section

				// use resource
				// nothing is done in this demo

				
				// acquire semaphore to decrement curCount
				// to show one less active thread
				// critical section for count variable update
				try 
				{
					mutexCounts.acquire();
				} catch(InterruptedException ie) { }
				curCount--;
				mutexCounts.release();	// leaving critical
							// section


// end of resource use crtical section 
// 				// comment out next line to see what
// 				happens without synchronization
				numResources.release();
			}
		}
	}

	public static void main(String[] args)
	 {

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
