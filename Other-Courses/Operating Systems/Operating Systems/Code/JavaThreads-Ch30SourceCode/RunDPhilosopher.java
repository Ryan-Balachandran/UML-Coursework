// A thread for the eat-think loop

public class RunDPhilosopher implements Runnable
{
   private static DPhilosopher dp;
   
   
   public void RunDPhilosopher(DPhilosopher d)
   {
      dp = d;
   }
   
   
   public void run()
   {
      dp.DPEatThink();  
   } // end run
 
} // end class RunDphilosopher

