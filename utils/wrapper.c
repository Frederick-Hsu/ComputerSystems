#include "wrapper.h"
#include "errhandler.h"

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

void Pause(void)
{
    (void)pause();
    return;
}

void Kill(pid_t pid, int signum)
{
    int rc = kill(pid, signum);
    if (rc < 0)
    {
        unix_error("Kill error");
    }
}

pid_t Fork(void)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        unix_error("Fork error");
    }
    return pid;
}

unsigned int Sleep(unsigned int seconds)
{
    unsigned rc;
    if ((rc = sleep(seconds)) < 0)
    {
        unix_error("Sleep error");
    }
    return rc;
}