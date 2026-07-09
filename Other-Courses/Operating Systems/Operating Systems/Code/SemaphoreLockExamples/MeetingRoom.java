// Meeting Room problem with Lock solution
import java.util.concurrent.locks.*;


public class MeetingRoom 
{
	static ReentrantLock l = new ReentrantLock();

	static int count = 0;

	static class Enter implements Runnable 
	{

		public void run() {
			for(int i = 0; i < 200_000; i++) 
			{
				// take lock l in try block and unlock
				// in finally block.  recommended way
				// to use locks in case an exception
				// occurs in critical section.  the lock
				// is always released.
				// comment out everything except for the 
				// count++; line to see what happens without
				// synchronization
				try 
				{
					l.lock();
					count++;
				} 
				finally 
				{
					l.unlock();
				}
			}
		}
	}

	static class Leave implements Runnable 
	{

		public void run() 
		{
			for(int i = 0; i < 200_000; i++) 
			{
				// take lock l in try block and unlock
				// in finally block.  recommended way
				// to use locks in case an exception
				// occurs in critical section.  the lock
				// is always released.
				// comment out everything except for the 
				// count++; line to see what happens without
				// synchronization
				try 
				{
					l.lock();
					count--;
				} finally 
				{
					l.unlock();
				}
			}
		}
	}

	public static void main(String [] args) 
	{
		Thread t1, t2;
		t1 = new Thread(new Enter());
		t2 = new Thread(new Leave());

		t1.start();
		t2.start();

		try 
		{
			t1.join();
			t2.join();
		} catch(InterruptedException ie) { }


		System.out.println("Count is " + count);

	}
}
