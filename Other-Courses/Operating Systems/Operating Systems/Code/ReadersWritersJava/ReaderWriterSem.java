// A multiple readers - single writer solution using binary semaphores.
// (Synchronization and mutual exclusion is implemented in the RWDatabase class.)
// T. Wilkes - 2020

import java.util.concurrent.*;


public class ReaderWriterSem {
   static final int NUM_WRITERS = 2; // number of writer threads
   static final int NUM_READERS = 10; // number of reader threads

   static RWDatabase db = new RWDatabase();
   
   
   // Driver for the readers-writers simulation
   public static void main(String [] args) 
   {
      // Create and start the reader threads
      Thread[] readers = new Thread[NUM_READERS];
      for(int i = 0; i < NUM_READERS; i++) 
      {
         readers[i] = new Thread(new Reader(i, db));
         readers[i].start();
      }

      // Create and start the writer threads
      Thread[] writers = new Thread[NUM_WRITERS];
      for(int i = 0; i < NUM_WRITERS; i++) 
      {
         writers[i] = new Thread(new Writer(i, db));
         writers[i].start();
      }
	  
      // The reader and writer threads will run continuously
      // until the user terminates the program.
   }
}
