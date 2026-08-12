/**
 * A  program illustrating the differences between
 * threads and processes.
 *
 * Most Unix/Linux/OS X users:
 * gcc thrd-vs-process.c -lpthread
 */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int value = 0; // shared between threads


/* the thread code */
void *runner(void *param)
{
    printf("CHILD process: new thread running, value = %d\n",value);
    value += 1;
    pthread_exit(0);
}


int main()
{
    pid_t pid;
    
    pthread_t tid1;
    pthread_attr_t attr1;
    
    pthread_t tid2;
    pthread_attr_t attr2;
    
    
    pid = fork();
    
    if (pid == 0)   /* child process */
    {
        pthread_attr_init(&attr1);
        pthread_attr_init(&attr2);
        
        pthread_create(&tid1,&attr1,runner,NULL);
        pthread_create(&tid2,&attr2,runner,NULL);
        
        pthread_join(tid1,NULL);
        pthread_join(tid2,NULL);
        
        printf("CHILD process: after thread join, value = %d\n",value); /* LINE C */
    }
    else if (pid > 0)   /* parent process */
    {
        wait(NULL);
        printf("PARENT process: value = %d\n",value); /* LINE P */
    } 
}

