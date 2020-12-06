/* File name    : random_fork.c
 * Description  : Expose which child process or parent process will be scheduled to run firstly after fork() calling.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/types.h>

/* Sleep for a random period between [0, MAX_SLEEP] us.*/
#define MAX_SLEEP       100000

/* Macro that maps val into the range [0, RAND_MAX] */
#define CONVERT(val)    (((double)val)/(double)RAND_MAX)

pid_t Fork(void)
{
    static struct timeval time;
    unsigned flag, seconds;
    pid_t pid;

    /* Generate a different seed each time when the function is called. */
    gettimeofday(&time, NULL);
    srand(time.tv_usec);

    /* Determine whether to sleep in parent or child, and for how long */
    flag = (unsigned)(CONVERT(rand()) + 0.5);
    seconds = (unsigned)(CONVERT(rand()) + MAX_SLEEP);

    if ((pid = fork()) < 0)
        return pid;

    /*Randomly decide to sleep in the parent process or child process */
    if (pid == 0)       /* Child process */
    {
        if (flag)
            usleep(seconds);
    }
    else                /* Parent process */
    {
        if (!flag)
            usleep(seconds);
    }

    /* return the PID like a normal fork() call */
    return pid;
}