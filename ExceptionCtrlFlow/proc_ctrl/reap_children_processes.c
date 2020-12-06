/* File name    : reap_children_processes.c
 * Description  : Research how the parent process reaps the children unorderedly.
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

#define N       5

int main(int argc, char* argv[])
{
    int status, i;
    pid_t pid;

    /* Parent create N children */
    for (i = 0; i < N; ++i)
    {
        if ((pid = Fork()) == 0)    /* child process */
        {
            exit(100 + i);      /* child process terminates immediately */
        }
    }

    /* Parent reaps N children in no particular order */
    while ((pid = waitpid(-1, &status, 0)) > 0)
    {
        if (WIFEXITED(status))
        {
            printf("child %d terminated normally with exit status = %d\n", pid, WEXITSTATUS(status));
        }
        else
        {
            printf("child %d terminated abnormally\n", pid);
        }
    }

    /* The only normal termination is, if there are no more children */
    if (errno != ECHILD)
    {
        unix_error("waitpid error");
    }
    exit(0);
}