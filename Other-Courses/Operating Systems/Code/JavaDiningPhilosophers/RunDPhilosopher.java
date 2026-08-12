// A thread for the eat-think loop

public class RunDPhilosopher implements Runnable
{
   private DPhilosopher dp;
   
   public RunDPhilosopher(DPhilosopher d)
   {
      dp = d;
   }

   
   @Override
   public void run()
   {
      dp.DPEatThink();  
   } // end run
 
} // end class RunDphilosopher
