#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <signal.h>

#include "../../utils/errhandler.h"

typedef void handler_t(int);

unsigned int Alarm(unsigned int seconds);
handler_t *Signal(int signum, handler_t *handler);

void handler(int sig)
{
    static int beeps = 0;
    printf("BEEP\n");
    if (++beeps < 5)
    {
        Alarm(1);
    }
    else
    {
        printf("BOOM!\n");
        exit(0);
    }
}

int main(int argc, char* argv[])
{
    Signal(SIGALRM, handler);       /* Install the SIGALRM handler */
    Alarm(1);       /* Next SIGALRM will be delivered in 1s */

    while (1)
    {
        ;           /* Signal handler returns control here each time */
    }
    exit(0);
}

handler_t *Signal(int signum, handler_t *handler)
{
    struct sigaction action, old_action;
    
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    if (sigaction(signum, &action, &old_action) < 0)
    {
        unix_error("Signal error");
    }
    return old_action.sa_handler;
}

unsigned int Alarm(unsigned int seconds)
{
    return alarm(seconds);
}