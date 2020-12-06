/* File name    : signal_proc1.c
 * Description  : 
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include "../../utils/user_defines.h"
#include "../../utils/errhandler.h"
#include "../../utils/wrapper.h"

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void handler(int signum);

int main(int argc, char* argv[])
{
    char buf[MAXBUF];

    if (signal(SIGCHLD, handler) == SIG_ERR)
    {
        unix_error("Signal error");
    }

    /* Parent creates children processes */
    for (int index = 0; index < 3; ++index)
    {
        if (Fork() == 0)
        {
            printf("Hello from child process ID: %d\n", (int)getpid());
            Sleep(1);
            exit(0);
        }
    }

    /* Parent waits for terminal input and then processes it */
    if (read(STDIN_FILENO, buf, sizeof(buf)) < 0)
    {
        unix_error("Read error");
    }

    printf("parent processing the input...\n");
    while (1)
    {
        ;
    }
    exit(0);
}

void handler(int signum)
{
    pid_t pid;
    if ((pid = waitpid(-1, NULL, 0)) < 0)
    {
        unix_error("Waitpid error");
    }
    printf("Handler reaped child process(pid = %d)\n", (int)pid);
    Sleep(2);
    return;
}