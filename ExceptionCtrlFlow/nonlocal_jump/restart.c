/* File name    : restart.c
 * Description  : When user press the Ctrl+c to interrupt a process, by using the nonlocal jump to restart itself.
 * 
 */

#include <stdio.h>
#include <signal.h>
#include <setjmp.h>
#include <unistd.h>

jmp_buf env;

void handler(int signum)
{
    siglongjmp(env, 1);
}

int main(int argc, char* argv[])
{
    signal(SIGINT, handler);

    if (!sigsetjmp(env, 1))
    {
        printf("\nstarting...\n");
    }
    else
    {
        printf("\nrestarting...\n");
    }

    while (1)
    {
        sleep(1);
        printf("\nprocessing...");
    }
    return 0;
}