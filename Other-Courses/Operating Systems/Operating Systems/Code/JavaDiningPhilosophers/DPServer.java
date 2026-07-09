/**
 * DPServer.java
 *
 * This class implements the methods called by the philosophers
 */

import java.util.Random;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;

public class DPServer
{

   private static Lock chopstick[] = new Lock[5]; // Create chopstick locks
   private static Lock mutex = new ReentrantLock(true);
   private static Lock countMutex = new ReentrantLock(true);   
   
   private static int count[] = new int[5]; // keep track of simultaneous use of chopsticks
   
   private static int MAX_EAT_TIME = 10; // maximum eating time in milliseconds
   private static int MAX_THINK_TIME = 100; // maximum thinking time in milliseconds
   private static Random r = new Random(0);

   
   // "default" constructor for DPServer class
   public DPServer()
   {
      System.out.println("Initializing chopstick locks...");
      for (int i = 0; i < 5; i++)
      {
         chopstick[i] = new ReentrantLock(true);
         count[i] = 0;
      } // end for
      System.out.println("Done initializing chopstick locks!");
      
   } // end DPServer default constructor


   // called by a philosopher when they wish to eat 
   public void takeChopsticks(int philosopherNumber)
   {
      // acquire chopstick[philosopherNumber] and chopstick[(philosopherNumber + 1) mod 5]
      mutex.lock();
      System.out.println("Acquiring chopstick[" + philosopherNumber + "] and chopstick[" + ((philosopherNumber + 1) % 5) + "]");
      chopstick[philosopherNumber].lock();
      chopstick[(philosopherNumber + 1) % 5].lock();
      mutex.unlock();
      
      countMutex.lock();
      count[philosopherNumber]++;
      count[(philosopherNumber + 1) % 5]++;
      for (int i = 0; i < 5; i++)
      {
         if (count[i] > 1)
         {
            System.out.println("***** More than one philosopher is using chopstick #" + i);
            System.exit(1);
         }
      }
      countMutex.unlock();
      
      // eat for a random number of milliseconds
      int eatTime = r.nextInt(MAX_EAT_TIME);
      System.out.println("Philosopher " + philosopherNumber + " is eating for " + eatTime + " milliseconds");
      try
      {
         Thread.sleep(eatTime);
      }
      catch (InterruptedException ex)
      {
         System.out.println("Philosopher " + philosopherNumber + " eatTime sleep was interrupted");
      }
         
      
   } // end takeChopsticks
  

   // called by a philosopher when they are finished eating 
   public void returnChopsticks(int philosopherNumber)
   {

      System.out.println("Releasing chopstick[" + philosopherNumber + "] and chopstick[" + ((philosopherNumber + 1) % 5) + "]");
      chopstick[philosopherNumber].unlock();
      chopstick[(philosopherNumber + 1) % 5].unlock();
      
            // release chopstick[philosopherNumber] and chopstick[(philosopherNumber + 1) mod 5]
      countMutex.lock();
      count[philosopherNumber]--;
      count[(philosopherNumber + 1) % 5]--;
      countMutex.unlock();

      // think for a random number of milliseconds
      int thinkTime = r.nextInt(MAX_THINK_TIME);
      System.out.println("Philosopher " + philosopherNumber + " is thinking for " + thinkTime + " milliseconds");
      try
      {
         Thread.sleep(thinkTime);
      }
      catch (InterruptedException ex)
      {
         System.out.println("Philosopher " + philosopherNumber + " thinkTime sleep was interrupted");
      }
   
      
   } // end returnChopsticks
   
} // end class DPServer
