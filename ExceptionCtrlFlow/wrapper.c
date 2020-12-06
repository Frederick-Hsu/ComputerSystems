#include "wrapper.h"
#include "syserror.h"

#include <sys/types.h>
#include <unistd.h>

pid_t Fork(void)
{
    pid_t pid = fork();
    if (pid < 0)
    {
        unix_error("Fork error");
    }
    return pid;
}