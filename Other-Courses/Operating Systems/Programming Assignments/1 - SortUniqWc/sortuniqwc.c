//
//  outline.c
//
//
//  Created by Ryan Balachandran on 10/7/20.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

#define READ_END    0
#define WRITE_END   1

int main(int argc, char *arv[])
{
    pid_t pid;
    
    int fd1[2];	// create first pipe fd1
    int fd2[2];	// create second pipe fd2
    
    
    
    // create the pipe
    if (pipe(fd1) == -1)
    {
        fprintf(stderr, "Pipe 1 failed");
        return 1;
    }
    else
    {
        pipe(fd1);
        printf("pipe 1 successful\n");
    }
    
    // fork first child
    pid = fork();	// create first child for sort
    
    if (pid < 0)	// fork error
    {
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if(pid == 0)	// first child process, run sort
    {
        printf("The child process running SORT pid = %d\n", getpid());
        dup2(fd1[WRITE_END], 1);				// tie write end of pipe fd1 to standard output (file descriptor 1)
        close(fd1[READ_END]);				    // close read end of pipe fd1
        execlp("/usr/bin/sort", "sort", NULL);	// start the sort command using execlp
        
        printf("Should not be here after execlp to SORT\n");        // should not get here
    }
    
    
    
    
    
    
    
    
    // create the pipe
    if (pipe(fd2) == -1)
    {
        fprintf(stderr, "Pipe 2 failed");
        return 1;
    }
    else
    {
        pipe(fd2);
        printf("pipe 2 successful\n");
    }
    
    // fork second child
    pid = fork();   // create second child for uniq
    
    if (pid < 0)    // fork error
    {
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0)   // second child process, run uniq
    {
        printf("The child process running UNIQ pid = %d\n", getpid());
        
        dup2(fd1[READ_END], 0);		// tie read end of fd1 to standard input (file descriptor 0)
        dup2(fd2[WRITE_END], 1);	// tie write end of fd2 to standard output (file descriptor 1)
        close(fd1[WRITE_END]);		// close write end of pipe fd1
        close(fd2[READ_END]);		// close read end of pipe fd2
        execlp("/usr/bin/uniq", "uniq", NULL);  // start the uniq command using execlp
        
        printf("Should not be here after execlp to UNIQ\n");    // should not get here
    }
    
    
    
    
    
    
    
    
    // fork third child
    pid = fork();	// create third child for wc -l
    
    if (pid < 0)    // fork error
    {
        fprintf(stderr, "Fork Failed\n");
        return 1;
    }
    else if (pid == 0)   // third child process, run wc -l
    {
        printf("The child process running wc -l pid = %d\n", getpid());
        dup2(fd2[READ_END], 0);	    // tie read end of fd2 to standard input (file descriptor 0)
        close(fd2[WRITE_END]);		// close write end of pipe fd2
        close(fd1[READ_END]);		// close read end of pipe fd1
        close(fd1[WRITE_END]);		// close write end of pipe fd1
        execlp("/usr/bin/wc", "wc", "-l", NULL);  // start the wc -l command using execlp
                
        printf("Should not be here after execlp to WC -l\n");   // should not get here
    }
    
    
    // parent process code
    // close both ends of pipes fd1 and fd2
    close(fd1[READ_END]);
    close(fd1[WRITE_END]);
    close(fd2[READ_END]);
    close(fd2[WRITE_END]);
    
    waitpid(pid, NULL, 0);	// wait for third process to end
    printf("LAST CHILD COMPLETE\n");
    
    
    return 0;
}
