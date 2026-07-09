// Barrier semaphore used to ensure that the Provider thread runs before
// the Reverser and UpperCaser threads begin
//
import java.util.concurrent.*;
import java.util.Scanner;

public class Sequencing {

	static Semaphore allow = new Semaphore(0, true);
	static String resource = null;

	static class Provider implements Runnable {
		public void run() {

			Scanner in = new Scanner(System.in);
			System.out.print("Enter a string: ");
			resource = in.next();
// comment out the the following line to see what happens without 
// synchronization
			allow.release(2);
		}
	}

	static class Reverser implements Runnable {

		public void run() {
// comment out the try block to see what happens with synchronization
			try {
				allow.acquire();
			} catch(InterruptedException ie) { }
			StringBuilder s = new StringBuilder();
			s.append(resource);
			System.out.println("Reverser says " + s.reverse());
		}
	}

	static class UpperCaser implements Runnable {

		public void run() {
// comment out the try block to see what happens with synchronization
			try {
				allow.acquire();
			} catch(InterruptedException ie) { }
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
