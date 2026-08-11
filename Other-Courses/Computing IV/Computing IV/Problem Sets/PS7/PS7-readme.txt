/**********************************************************************
 *  readme.txt template                                                   
 *  Kronos PS7a startup
 **********************************************************************/

Name: Ryan Balachandran

Hours to complete assignment: ~30+

/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/

 I was able to complete the whole assignment. 
 Taking in the name of the file to parse was easy.

 Figuring out how to parse the file to find the start of the boot sequence
 and when it complete was hard.

 I was able to search through the file with a while loop and use regular 
expressions to find (log.c.166) server started and oejs.AbstractConnector...
 to find when the boot is complete.

I have one if statement to find the first iteration of (log.c.166) to find 
the start of the boot sequence. I then had another if statement that if 
another boot sequence is found before the boot complete sequence, then it
 is an incomplete boot, otherwise I search for the boot complete sequence 
and find the elapsed time between the boot start and boot complete sequence.


/**********************************************************************
 *  Copy here all regex's you created for parsing the file, 
 *  and explain individually what each ones does.
 **********************************************************************/
  
 boot_start = ".*log.c.166.*";
 boot_complete = ".*oejs.AbstractConnector:Started SelectChannelConnector.*";

 string match_time = "(\\d{2}):(\\d{2}):(\\d{2})";
 string match_date = "(\\d{4})-(\\d{2})-(\\d{2})";

 regex e = regex(boot_start);
 regex ea = regex(boot_complete);

 regex elapsed_time(match_time);
 regex getdate(match_date);

 regex e searches for the string sequence that indicates the start of the 
 boot up sequence. Finding a second sequence before the boot complete 
 sequence means the boot up failed.

 regex ea searches for the string sequence that indicates that the boot 
 up sequence is complete.

 regex elapsed_time searches for the time accompanying the first match 
 of the boot up start sequence. It is saved to a string time1.

 It is used again to search for the time accompanying the boot complete sequence. It is saved to a string time2.

 regex getdate searches for the date accompanying the first boot up sequence.

/**********************************************************************
 *  Describe your overall approach for solving the problem.
 *  100-200 words.
 **********************************************************************/

 My approach was to get the filename from the command line, then send 
 the file to a function called parse. parse appends .rpt to the end of 
 the file and creates a new text file.

 I created strings that help the regular expression that the program is 
 going to use to find the startup sequence, bootup complete sequence, date, and time.

 I used a while loop to search through each line of the file with an integer
 line_number being incremented through each iteration to keep track of the 
 line number the match was found on. 

 I first have an if statement that checks if the line matches the regular 
 expression for the server startup. Within the if statement I have a bool 
 variable that is set at the end of the previous if statement if another server
 startup sequence is found again. I then use regex_search to store the match in 
 a smatch variable where I then append to a tempory string variable and output 
 the line number, log name, start date, and start time into the file I appended .rpt to earlier.

 After I have another if statement to search the file for the boot complete 
 sequence, using regex_search again to find the time and output it to the 
 file before calculating the elapsed time between the boot up sequence and the boot complete sequence.




