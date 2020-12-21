/* File name    : hello_multithreading.c
 * Description  : The first multithreading program with POSIX threads.
 * 
 */

#include <pthread.h>

#include <stdio.h>
#include <stdlib.h>

void* thread(void* pargv);

int main(int argc, char* argv[])
{
    pthread_t thid;
    pthread_create(&thid, NULL, thread, NULL);
    pthread_join(thid, NULL);

    printf("thid = %ld\n", thid);
    
    exit(0);
}

void* thread(void* pargv)
{
    printf("Hello, multi-threading.\n");

    printf("Myself thread ID = %ld\n", pthread_self());
    return NULL;
}