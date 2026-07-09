// Code for the Writer threads.
// T. Wilkes - 2020

public class Writer implements Runnable 
{
   
   private int myID;
   private RWDatabase db;
   
   public Writer(int i, RWDatabase d) 
   {
      myID = i;
      db = d;
   }

   @Override
   public void run() 
   {
      while (true) 
      {
         db.write(myID);
      }
   }
}
