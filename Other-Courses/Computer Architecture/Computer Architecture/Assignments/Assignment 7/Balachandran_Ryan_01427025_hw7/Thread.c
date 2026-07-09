// Help file for cs305 Assignment 7
//
// This file has some code and many comments
// to direct you through assignment #7

// need these include files

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <string.h>

// need just a main function, no arguments
int main(void)
{
    // local variables
    pid_t   pid, ppid;
    int     ruid, rgid, euid, egid;
    int     priority;
    char    msg_buf[100];
    int     msg_pipe[2];

    // use the pipe() system call to create the pipe
    if (pipe(msg_pipe) == -1)
    {
        perror("failed in Parent pipe creation:");
        exit(7);
    }

    // use varous system calls to collect and print process details
    printf("\nThis is the Parent process report:\n");

    pid  = getpid();
    ppid = getppid();
    ruid = getuid();
    euid = geteuid();
    rgid = getgid();
    egid = getegid();
    priority = getpriority(PRIO_PROCESS, 0);

    printf("\nPARENT PROG:  Process ID is:\t\t%d\n", pid);
    printf("PARENT PROC:  Process parent ID is:\t%d\n", ppid);
    printf("PARENT PROC:  Real UID is:\t\t%d\n", ruid);
    printf("PARENT PROC:  Real GID is:\t\t%d\n", rgid);
    printf("PARENT PROC:  Effective UID is:\t\t%d\n", euid);
    printf("PARENT PROC:  Effective GID is:\t\t%d\n", egid);
    printf("PARENT PROC:  Process priority is:\t%d\n", priority);

    printf("\nPARENT PROC: will now create child, write pipe, and do a normal termination\n");

    // use the sprintf() call to build a message to write into the pipe
    // and dont forget to write the message into the pipe before parent exits
    sprintf(msg_buf, "\nThis is the pipe message from the parent with %d PID\n", pid);

    // now use the fork() call to create the child:
    switch(pid = fork())
    {
        // if the call fails
        case -1:
            perror("Fork call failed: ");
            exit(1);

        // this is the parent's case
        default:
            printf("\nPARENT PROG: Created child with %d PID\n", pid);
            write(msg_pipe[1], msg_buf, strlen(msg_buf));
            exit(1);

        // this is the child's case
        case 0:
            printf("\nThis is the Child process report:\n");

            pid  = getpid();
            ppid = getppid();
            ruid = getuid();
            euid = geteuid();
            rgid = getgid();
            egid = getegid();
            priority = getpriority(PRIO_PROCESS, 0);

            printf("\nCHILD PROG:  Process ID is:\t\t%d\n", pid);
            printf("CHILD PROC:  Process parent ID is:\t%d\n", ppid);
            printf("CHILD PROC:  Real UID is:\t\t%d\n", ruid);
            printf("CHILD PROC:  Real GID is:\t\t%d\n", rgid);
            printf("CHILD PROC:  Effective UID is:\t\t%d\n", euid);
            printf("CHILD PROC:  Effective GID is:\t\t%d\n", egid);
            printf("CHILD PROC:  Process priority is:\t%d\n", priority);

            printf("\nCHILD PROG: about to read pipe and report parent message:\n\n");

            read(msg_pipe[0], msg_buf, 100);
            printf("CHILD PROC: parent's msg is: %s\n", msg_buf);
            printf("CHILD PROC: Process parent ID now is: %d\n", getppid());
            printf("CHILD PROC: ### Goodbye ###\n");
            exit(1);
    }   // switch and child end

    return 0;
}
