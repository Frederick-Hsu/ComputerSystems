/* File name    : fork.c
 * Description  : How to create the child process.
 *
 */

#include "../liberror/errhandler.h"
#include "../liberror/errwrapper.h"

#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    pid_t pid;
    int x = 1;

    pid = Fork();
    if (pid == 0)   /* Child process */
    {
        printf("child process : x = %d\n", ++x);
        printf("child PID = %d\n", getpid());
        printf("child process' parent PID = %d\n\n", getppid());
        exit(0);
    }

    /* Parent process */
    printf("parent process : x = %d\n", --x);
    printf("parent PID = %d\n", getpid());
    printf("parent process' parent PID = %d\n\n", getppid());
    exit(0);
}