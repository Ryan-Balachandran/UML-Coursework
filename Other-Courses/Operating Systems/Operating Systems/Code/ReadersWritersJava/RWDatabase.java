// The database for the multiple readers - single writer simulation.
// Synchronization between the readers & writers is implemented in this class.
// T. Wilkes - 2020

import java.util.concurrent.*;
import java.util.Random;


public class RWDatabase 
{

   // This binary semaphore is used to synchronize between reader and writer threads.
   // No readers will be allowed to access the database if a writer is active,
   // and no writer will be allowed to access the database if any readers are active;
   // also, mutual exclusion is enforced between writers.
   static Semaphore rw_semaphore = new Semaphore(1, true);
   
   // This binary semaphore is used for mutual exclusion between reader threads
   // when they update reader_count.
   static Semaphore reader_mutex = new Semaphore(1, true);

   static int reader_count = 0;
   static int writer_count = 0; // Should never be > 1!
   
   static int database = 0; // The shared data
   
   static Random rand = new Random(); // Random number generator for sleep times


   public void write(int writerID) 
   {
      // Acquire the RW semaphore to enter the critical section
      try 
      {
         rw_semaphore.acquire();
      } catch(InterruptedException ie) {}

      writer_count++;
                       
      // Check for correct synchronization
      if ((writer_count > 1) || (reader_count > 0)) 
      {
         System.out.println("***** In Writer thread #" + writerID
                            + ": Writer count is " + writer_count
                            + ", reader count is " + reader_count
                            + ", terminating! *****");
         System.exit(-1);
      }
            
      // Write to the database
      database++;
      System.out.println("Writer #" + writerID + " wrote new value = " + database);
            
      // Leave the critical section by releasing the RW semaphore
      writer_count--;
      rw_semaphore.release();

      // Pause for up to 100 msec to give another thread a chance      
      try 
      {
         Thread.sleep(rand.nextInt(100));
      } catch(InterruptedException ie) {}
   }


   public void read(int readerID) 
   {
      // Create a critical section to increment the reader count
      try 
      {
         reader_mutex.acquire();
      } catch(InterruptedException ie) {}
          
      if (reader_count == 0) { // First reader in; wait for an active writer (if any) to finish
         try {
            rw_semaphore.acquire();
         } catch(InterruptedException ie) {}
      }

      reader_count++;
 
      reader_mutex.release(); // End of critical section for incrementing the reader count
           
      // Check for correct synchronization
      if (writer_count > 0) 
      {
         System.out.println("***** In Reader thread #" + readerID
                            + ": Writer count is " + writer_count
                            + ", reader count is " + reader_count
                            + ", terminating! *****");
         System.exit(-1);
      }

      // Read from the database
      System.out.println("\tReader #" + readerID + " read value = " + database);
            
      // Create a critical section to decrement the reader count
      try 
      {
         reader_mutex.acquire();
      } catch(InterruptedException ie) {}
            
      reader_count--;
            
      if (reader_count == 0) { // Last reader out; signal a waiting writer (if any)
         rw_semaphore.release();
      }
      reader_mutex.release(); // End of critical section for decrementing the reader count

      // Pause for up to 100 msec to give another thread a chance      
      try 
      {
         Thread.sleep(rand.nextInt(100));
      } catch(InterruptedException ie) {}
   }
}
