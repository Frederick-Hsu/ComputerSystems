/* File name    : waitprob.c
 * Desicptrion  : How to wait for a child pocress stopped or terminated.
 * 
 */

#include <stdio.h>
#include <stdlib.h>

#include "../liberror/errhandler.h"
#include "../liberror/errwrapper.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char* argv[])
{
    pid_t pid = Fork();
    if (pid== 0)
    {
        printf("child process(%d): a\n", getpid());
        fflush(stdout);
    }
    else
    {
        printf("parent process(%d): b\n", getpid());
        fflush(stdout);
        waitpid(-1, NULL, 0);       /* wait for the child process to terminate */
    }
    printf("process pid = %d, c\n", getpid());
    fflush(stdout);
    exit(0);
}