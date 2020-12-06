#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <signal.h>
#include <unistd.h>

#include "../../utils/wrapper.h"

int main(int argc, char* argv[], char* envp[])
{
    pid_t pid;

    /* child process sleeps until SIGKILL signal received, then dies */
    if ((pid = Fork()) == 0)
    {
        Pause();    /* wait for a signal to arrive */
        printf("control should never reach here!\n");
        exit(0);
    }

    /* parent process sends a SIGKILL signal to the child process */
    Kill(pid, SIGKILL);
    printf("Send SIGKILL signal to child process.\n");
    exit(0);
}