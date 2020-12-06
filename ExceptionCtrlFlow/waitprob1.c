#include <stdio.h>
#include <stdlib.h>

#include "../liberror/errhandler.h"
#include "../liberror/errwrapper.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    int status;
    pid_t pid;

    printf("Hello\n");
    pid = Fork();
    printf("!pid = %d\n", !pid);

    if (pid != 0)
    {
        if ((waitpid(-1, &status, 0)) > 0)
        {
            if (WIFEXITED(status) != 0)
            {
                printf("exit status = %d\n", WEXITSTATUS(status));
            }
        }
    }
    printf("process (pid = %d) Bye\n", getpid());
    exit(2);
}