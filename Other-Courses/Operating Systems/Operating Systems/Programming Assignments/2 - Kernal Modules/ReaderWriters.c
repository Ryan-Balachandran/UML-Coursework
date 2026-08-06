//
//  outline.c
//
//
//  Created by Ryan Balachandran on 10/7/20.
//

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

// These are the globals shared by all threads, including main
#define RANGE 1000000000
#define BASE 500000000
int rICrange = RANGE;
int rICbase = BASE;
int rOOCrange = RANGE;
int rOOCbase = BASE;
int wICrange = RANGE;
int wICbase = BASE;
int wOOCrange = RANGE;
int wOOCbase = BASE;
int keepgoing = 1;
int totalReaders = 0;
int totalWriters = 0;

/* The global area ust include semaphore  declarations and
    declarations of any state variables (reader counts,
    total number of readers and writers). */


// Use this function to sleep within the threads
void threadSleep(int range, int base)
{
    structs timespec t;
    t.tv_sec = 0;
    t.tv_nsec = (rand() % range) + base;
    nanosleep(&t, 0);
}


void *readers(void *args)
{
    int id = *((int *) args);
    
    threadSleep(rOOCrange, rOObase);
    
    while (keepgoing)
    {
        /* Add code for each reader to enter the reading area.
           The totalReaders variable must be incremented just before entering
           the reader area. */
        
        printf("Reader %d starting to read\n", id);
        
        threadSleep(rICrange, rICbase);
        
        printf("Reader %d finishing reading\n", id);
        
        /* Add code for each reader to leave the reading area. */
        
        threadSleep(rOOCrange, rOOCbase);
    }
    
    printf("Reader %d quitting\n", id);
}


void *writers(void *args)
{
    int id = *((int *) args);
    
    threadSleep(wOOCrange, wOOCbase);
    
    while (keepgoing)
    {
        /* Add code for each writer to enter the writing area */
        
        totalWriters++;
        printf("Writer %d starting to write\n", id);
        
        threadSleep(wICrange, wICbase);
        
        printf("Writer %d finishing writing\n", id);
        
        /* Add code for each writer to leave the writing area. */
        
        threadSleep(rOOCrange, rOOCbase);
    }
    
    printf("Writer %d quitting\n", id);
}


int main(int argc, har **argv)
{
    int numRThreads = 0;
    int numWThreads = 0;
    
    if (argc == 11)
    {
        rICrange = atoi(argv[1]);
        rICbase = atoi(argv[2]);
        rOOCrange = atoi(argv[3]);
        rOOCbase = atoi(argv[4]);
        wICrange = atoi(argv[5]);
        wICbase = atoi(argv[6]);
        wOOCrange = atoi(argv[7]);
        wOOCbase = atoi(argv[8]);
        numRThreads = atoi(argv[9]);
        numWThreads = atoi(argv[10]);
    }
    else
    {
        printf("Usage: %s <reader in critical section sleep range> <reader in critical section sleep base> \n\t <reader out of critical section sleep range> <reader out of critical section sleep base> \n\t <writer in critical section sleep range> <writer in critical  section sleep base> \n\t  <writer out of critical section sleep range> <writer out of critical section sleep base> \n\t <number of readers> <number of writers>\n", argv[0]);
        
        exit(-1);
    }
    
    /* Add declarations for pthread arrays, one for reader threads and
       one for writer threads. */
    
    /* Add declarations for arrays for reader and writer thread identities. As in the
       dining philosopher problem, arrays of int are used. */
    
    /* Add code to initialize the binary semaphores used by the readers and writers. */
    
    /* Add a for loop to create numRThread reader threads. */
    
    /* Add a for loop to create numWThread writer threads. */
    
    // These statements wait for the user to type a character and press
    // the Enter key. Then, keepgoing will be set to 0, which will cause
    // the reader and writer threads to quit.
    
    char buf[256];
    scanf("%s", &buf);
    keepgoing = 0;
    
    /* Add two for loops using pthread_join in order to wait for the reader
       and writer threads to quit. */
    
    printf("Total number of reads: %d\nTotal number of writes: %d\n", totalReaders, totalWriters);
}
