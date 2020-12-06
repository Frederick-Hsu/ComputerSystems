#include <stdio.h>
#include <stdlib.h>

#include "../../utils/errhandler.h"

#include <unistd.h>
#include <signal.h>

/* SIGINT handler */
void handler(int signum)
{
    exit(0);
}

unsigned int snooze(unsigned int seconds);

int main(int argc, char* argv[], char* envp[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <seconds>\n", argv[0]);
        exit(0);
    }

    if (signal(SIGINT, handler) == SIG_ERR)
    {
        unix_error("Signal error");
    }
    snooze(atoi(argv[1]));

    return 0;
}

unsigned int snooze(unsigned int seconds)
{
    unsigned int rc = sleep(seconds);
    printf("Slept for %u of %u seconds.\n", seconds - rc, seconds);
    return rc;
}