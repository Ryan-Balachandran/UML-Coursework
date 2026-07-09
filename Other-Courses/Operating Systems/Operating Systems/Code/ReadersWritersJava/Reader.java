// Code for the Reader threads.
// T. Wilkes - 2020

public class Reader implements Runnable 
{

   private int myID;
   private RWDatabase db;
   
   public Reader(int i, RWDatabase d) 
   {
		myID = i;
		db = d;
   }

   @Override
   public void run() 
   {
      while (true) 
      {
         db.read(myID);
      }
   }
}
