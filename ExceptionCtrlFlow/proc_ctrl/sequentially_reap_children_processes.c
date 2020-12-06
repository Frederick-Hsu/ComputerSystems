/* File name    : sequentially_reap_children_processes.c
 * Description  : By using the waitpid() to reap the children processes, accodring to the 
 *              : sequence order which are created. 
 * Creator      : Frederique Hsu
 * Creation date: Mon.  16 Nov. 2020
 * Copyright(C) 2020    All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "../../liberror/errhandler.h"
#include "../../liberror/errwrapper.h"

#include <sys/types.h>
#include <sys/wait.h>

#define N       8


int main(int argc, char* argv[])
{
    int status, i;
    pid_t pid[N], retpid;

    /* Parent creates N children */
    for (i = 0; i < N; ++i)
    {
        if ((pid[i] = Fork()) == 0)
        {
            exit(100+i);        /* child process terminates immediately, become a zombie process */
        }
    }

    /* Parent reaps N children in order */
    i = 0;
    while ((retpid = waitpid(pid[i+1], &status, 0)) > 0)
    {
        if (WIFEXITED(status))
        {
            printf("child %d terminated normally with exit status = %d\n", retpid, WEXITSTATUS(status));
        }
        else
        {
            printf("child %d terminated abnormally\n", retpid);
        }
    }

    /* The only normal termination is, if there are no more children */
    if (errno != ECHILD)
    {
        unix_error("waitpid error");
    }
    exit(0);
}