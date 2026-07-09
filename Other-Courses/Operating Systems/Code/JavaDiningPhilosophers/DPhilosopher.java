// implementation of the Dining Philosopher class

public class DPhilosopher
{
   private int dpNum;
   private DPServer dpServ;
   
   // value constructor for the DPhilosopher class
   public DPhilosopher(int num, DPServer d)
   {
      dpNum = num;
      dpServ = d;
   } // end DPhilosopher value constructor
   
 
   public void DPEatThink()
   {   
      while (true)
      {
         // get ready to eat
         System.out.println("Philosopher " + dpNum + " is getting ready to eat");
         dpServ.takeChopsticks(dpNum);
            
         // finish eating
         System.out.println("Philosopher " + dpNum + " is finished eating");
         dpServ.returnChopsticks(dpNum);
         
      } // end while
   
   } // end DPEatThink

} // end class DPhilosopher
