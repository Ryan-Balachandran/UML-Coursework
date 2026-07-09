// Meeting Room problem solution using a binary semaphore
import java.util.concurrent.*;


public class MeetingRoomSem 
{
	static Semaphore s = new Semaphore(1, true);

	static int count = 0;

	static class Enter implements Runnable 
	{

		public void run() 
		{
			for(int i = 0; i < 200_000; i++) 
			{
				// take the semaphore to enter the 
				// critical section
				// comment out the try block to see what
				// happens without synchronization
				try 
				{
					s.acquire();
				} catch(InterruptedException ie) {}
				count++;
				// leave the critical section by releasing
				// the semaphore
				// comment next line to see what happens
				// without synchronization
				s.release();
			}
		}
	}

	static class Leave implements Runnable
	 {

		public void run() 
		{
			for(int i = 0; i < 200_000; i++) 
			{
				// take the semaphore to enter the 
				// critical section
				// comment out the try block to see what
				// happens without synchronization
				try 
				{
					s.acquire();
				} 
				catch(InterruptedException ie) { }
				count--;
				// leave the critical section by releasing
				// the semaphore
				// comment next line to see what happens
				// without synchronization
	   		s.release();
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
