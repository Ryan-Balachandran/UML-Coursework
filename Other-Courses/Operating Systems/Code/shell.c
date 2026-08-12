/**
 * A simple shell using the fork()/exec() system calls.
 *
 * based on Figure 3.08 by
 * @author Silberschatz, Galvin, and Gagne
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

// Updated by T. Wilkes July 2020

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    
    char command[80];
    
    while (1)
    {
        printf("tomsh> ");
        scanf("%s", command);
        fflush(stdout);
        
        /* fork a child process */
        pid = fork();
        
        if (pid < 0)    /* error occurred */
        {
            fprintf(stderr, "*** Fork Failed\n");
            return 1;
        }
        else if (pid == 0)  /* child process */
        {
            printf("*** I am the child, pid == %d\n\n", pid);
            fflush(stdout);
            execlp(command, "", NULL);
        }
        else    /* parent process */
        {
            /* parent will wait for the child to complete */
            printf("*** I am the parent, child pid == %d\n\n", pid);
            fflush(stdout);
            wait(NULL);
            
            printf("\n*** Child Complete\n\n");
        }
    }
    
    return 0;
}
