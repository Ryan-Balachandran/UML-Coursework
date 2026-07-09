import java.util.Scanner;

public class Bankers
{

   private int nProcesses;   // Number of processes
   private int nResources;   // Number of resources
   
   private int allocate[][]; // Resources allocated to each process
   private int max[][];      // Maximum demand of each process
   private int avail[][];    // Number of available resource instances
   private int need[][];     // Remaining resources needed per process
      
   private void input()
   {
      Scanner sc = new Scanner(System.in);
      
      System.out.print("\nEnter no. of Processes and Resources : ");
      
      nProcesses=sc.nextInt();  //no. of process
      nResources=sc.nextInt();  //no. of resources
      
      // Initialize arrays
      allocate = new int[nProcesses][nResources];
      max      = new int[nProcesses][nResources];
      avail    = new int[1][nResources];
      need     = new int[nProcesses][nResources];
      
      // Fill input arrays
      System.out.println("\nEnter Allocation matrix -->");
      
      for(int i=0; i<nProcesses; i++)
         for(int j=0; j<nResources; j++)
            allocate[i][j] = sc.nextInt();  //allocation matrix
       
      System.out.println("\nEnter Max matrix -->");
      
      for(int i=0; i<nProcesses; i++)
         for(int j=0; j<nResources; j++)
            max[i][j] = sc.nextInt();  //max matrix
       
      System.out.println("\nEnter Available matrix -->");
      
      for(int j=0; j<nResources; j++)
         avail[0][j] = sc.nextInt();  //available matrix
         
      sc.close(); // No more input needed
      
   } // end input
     
   //calculating need matrix
   private int[][] calc_need()
   {
      for(int i=0; i<nProcesses; i++)
         for(int j=0; j<nResources; j++)
            need[i][j] = max[i][j] - allocate[i][j];
        
      return need;
      
   } // end calc_need
    
   private void show_need() 
   {
      System.out.println("\nNeed matrix -->");
      
      for(int i=0; i<nProcesses; i++) 
      {
         for(int j=0; j<nResources; j++) 
         { //calculating need matrix
            System.out.print(need[i][j] + " ");
         } // end nResources
         
         System.out.println();
         
      } // end nProcesses
      
      System.out.println();
      
   } // end show_need
  
   private boolean check(int i)
   {
       //checking if all resources for ith process can be allocated
      for(int j=0; j<nResources; j++)
      { 
         if(avail[0][j] < need[i][j])
            return false;
      }
      return true;
      
   } // end check
 
   public void isSafe()
   {
   
      input();
      calc_need();
      show_need();
      
      boolean done[]=new boolean[nProcesses];
      int j=0;
   
      while(j < nProcesses)
      {  //until all process allocated
      
         boolean allocated = false;
         
         for(int i=0; i<nProcesses; i++)
         {
            if(!done[i] && check(i))
            {  //trying to allocate
               for(int k=0; k<nResources; k++)
               {
                  avail[0][k]=avail[0][k]-need[i][k]+max[i][k];
               }
               System.out.println("Allocated process : "+i);
               allocated = done[i] = true;
               j++;
            } // end if
            
         } // end nProcesses
            
         if(!allocated) 
            break;  //if no allocation
            
      }// end process loop
      
      if(j == nProcesses)  // if all processes are allocated
         System.out.println("\nSafely allocated");
      else
         System.out.println("\nNot all processes could be allocated safely");
         
   } // end isSafe
     
   public static void main(String[] args) 
   {
      new Bankers().isSafe();
   } // end Main
   
}
