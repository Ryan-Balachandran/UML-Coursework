// Sequencing processes using a Lock object with an associated condition object
// and state variable
import java.util.concurrent.locks.*;
import java.util.Scanner;

public class SequencingLockAndCV {

	static ReentrantLock allow = new ReentrantLock(true);
	static Condition allowCV = allow.newCondition();
	static int numAllowedToGo = 0;

	static String resource = null;

	static class Provider implements Runnable {
		public void run() {

			Scanner in = new Scanner(System.in);
			System.out.print("Enter a string: ");
			resource = in.next();
// comment out try block and finally to see what happens without synchronization
			try {
				allow.lock();
				numAllowedToGo = 2;	// two threads are allowed to proceed
				allowCV.signalAll();	// wake up ALL threads waiting on condition
			} finally {
				allow.unlock();		// release the lock
			}
		}
	}

	static class Reverser implements Runnable {

		public void run() {
// comment out try block and finally to see what happens without synchronization
			try {
				allow.lock();
				while (numAllowedToGo == 0)	// state variable must be greater that
								// zero before the thread can perform task
					try {
						allowCV.await();  	// wait till signalled and then recheck condition
					} catch(InterruptedException ie) { }
			} finally {
				allow.unlock();
			}
			// mutual exclusion is not needed because the shared variable resource is used
			// read only
			StringBuilder s = new StringBuilder();
			s.append(resource);
			System.out.println("Reverser says " + s.reverse());
		}
	}

	static class UpperCaser implements Runnable {

		public void run() {
// comment out try block and finally to see what happens without synchronization
			try {
				allow.lock();
				while (numAllowedToGo == 0)	// state variable must be greater that
								// zero before the thread can perform task
					try {
						allowCV.await();  	// wait till signalled and then recheck condition
					} catch(InterruptedException ie) {  }
			} finally {
				allow.unlock();
			}
			System.out.println("UpperCaser says " + resource.toUpperCase());
		}
	}

	public static void main(String [] args) {

		Thread[] tList = new Thread[3];
		tList[0] = new Thread(new Provider());
		tList[1] = new Thread(new Reverser());
		tList[2] = new Thread(new UpperCaser());

		for(Thread t : tList)
			t.start();

		for(Thread t: tList)
			try {
				t.join();
			} catch(InterruptedException ie) { }
	}
}
