/**********************************************************************
 *  readme template                                                   
 *  DNA Sequence Alignment
 **********************************************************************/

Name: Ryan Balachandran
Login:

Hours to complete assignment (optional): +30

/**********************************************************************
 *  Explain what you did to find the alignment itself.
 **********************************************************************/

 I used the Needlemen Wunsch algorithm.

 I made a while loop with variables i and j.

 the first if statement looked to see if the characters of string 1 and 2 were the same.
 Otherwise they would go to 2 else if statements, looking to see if the number in the 
 matrix cell below plus two is the same as the current one, then I would
 add a space for string 2.
 Or, if the number in the cell to the right plus two is the same as the current one,
 I would add a space for string 1.  
 The ending else statement was if the characters were different, then I would still
 print them and move diagonally with a cost of 1.

/**********************************************************************
 * Does your code work correctly with the endgaps7.txt test file? 
 * 
 * This example should require you to insert a gap at the beginning
 * of the Y string and the end of the X string.
 **********************************************************************/
Input: x = atattat
       y = tattata

Expected output: atattat-
	         -tattata

What happened:	atattat
                -tattat

/**********************************************************************
 *  How much main memory does your computer have? Typical answers
 *  are 2 GB to 16 GB.
 **********************************************************************/

 My main Mac Computer has 8 GB.
 The virtual box has 1024 MB.

/**********************************************************************
 *  For this question assume M=N. Look at your code and determine
 *  approximately how much memory it uses in bytes, as a function of 
 *  N. Give an answer of the form a * N^b for some constants a 
 *  and b, where b is an integer. Note chars are 2 bytes long, and 
 *  ints are 4 bytes long.
 *
 *  Provide a brief explanation.
 *
 *  What is the largest N that your program can handle if it is
 *  limited to 8GB (billion bytes) of memory?
 **********************************************************************/
 
 If M = N is the size of the string
 a and b is the number of bytes in the string
 
 For examples:
 X = atattat
 Y = tattata

 a = 2*7 = 14
 b = 2*7 = 14

 a * N^b

 14 * 7^14 = 9.495123e+12

 largest N =

/**********************************************************************
 *  Were you able to run Valgrind's massif tool to verify that your
 *  implementation uses the expected amount of memory?
 *
 *  Answer yes, no, I didn't try, I tried and failed, or I used a 
 *  different tool.
 *
 *  If yes, paste in the ms_print top chart of memory use over time,
 *  and also indicate which file your code was solving.
 * 
 *  Explain if necessary.
/**********************************************************************

 I used the gene57.txt file in the sequence folder

    KB
91.69^                             :                                          
     |                         #:::@::::::::::::::::::::::::::::::::::::::::::
     |                         #   @                                         :
     |                         #   @                                         :
     |                        @#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
     |                       :@#   @                                         :
   0 +----------------------------------------------------------------------->Mi
     0                                                                   7.208


/**********************************************************************
 *  For each data file, fill in the edit distance computed by your
 *  program and the amount of time it takes to compute it.
 *
 *  If you get segmentation fault when allocating memory for the last
 *  two test cases (N=20000 and N=28284), note this, and skip filling
 *  out the last rows of the table.
 **********************************************************************/

data file           distance       time (seconds)     memory (MB)
------------------------------------------------------------------
ecoli2500.txt	      118              0.119553          24.05
ecoli5000.txt         160              0.515815          95.71
ecoli7000.txt         194              1.010119          187.4
ecoli10000.txt        223              2.042053          382.1
ecoli20000.txt        killed
ecoli28284.txt        killed

/*************************************************************************
 *  Here are sample outputs from a run on a different machine for 
 *  comparison.
 ************************************************************************/

data file           distance       time (seconds)
-------------------------------------------------
ecoli2500.txt          118             0.171
ecoli5000.txt          160             0.529
ecoli7000.txt          194             0.990
ecoli10000.txt         223             1.972
ecoli20000.txt         3135            7.730


/**********************************************************************
 *  For this question assume M=N (which is true for the sample files 
 *  above). By applying the doubling method to the data points that you
 *  obtained, estimate the running time of your program in seconds as a 
 *  polynomial function a * N^b of N, where b is an integer.
 *  (If your data seems not to work, describe what went wrong and use 
 *  the sample data instead.)
 *
 *  Provide a brief justification/explanation of how you applied the
 *  doubling method.
 * 
 *  What is the largest N your program can handle if it is limited to 1
 *  day of computation? Assume you have as much main memory as you need.
 **********************************************************************/

 a = 
 b = 
 largest N = 


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
 
 I did not have many problems except trying to get endgaps7.txt to work.
 The two strings were:

 X = atattat
 Y = tattata

 The expected output was:
 
 X = atattat-
 Y = -tattata

 But I got:

 X = atattat
 Y = -tattat








