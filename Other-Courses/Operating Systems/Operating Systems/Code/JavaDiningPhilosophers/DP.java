// Dining Philosophers test program

import java.util.concurrent.*;

public class DP
{ 
   public static void main(String[] args)
   {
      DPServer dps = new DPServer();
      System.out.println("DPServer created");
      DPhilosopher dp[] = new DPhilosopher[5];
      RunDPhilosopher dpTask[] = new RunDPhilosopher[5];
      Thread dpThread[] = new Thread[5];
   
    // Create and launch the DPhilosopher threads
      for (int i = 0; i < 5; i++)
      {
         dp[i] = new DPhilosopher(i, dps);
         dpTask[i] = new RunDPhilosopher(dp[i]);
         dpThread[i] = new Thread(dpTask[i]);
         dpThread[i].start();
      }
       
   } // end main
  
} // end class DP
