#include <stdio.h>
#include <stdlib.h>

#include "../../utils/errhandler.h"

#include <unistd.h>
#include <signal.h>

void handler(int signum);

int main(int argc, char* argv[])
{
    /* Install the SIGINT handler */
    if (signal(SIGINT, handler) == SIG_ERR)
    {
        unix_error("Signal error");
    }
    pause();    /* Wait for the receipt of a signal */
    exit(0);
}

void handler(int signum)    /* SIGINT handler */
{
    printf("\nCaught SIGINT\n");
    exit(0);
}