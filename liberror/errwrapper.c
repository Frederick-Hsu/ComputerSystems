#include "errwrapper.h"
#include "errhandler.h"

#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <netdb.h>
#include <stdlib.h>


pid_t Wait(int* status)
{
    pid_t pid = wait(status);
    if (pid < 0)
    {
        unix_error("Wait error");
    }
    return pid;
}
    
void Kill(pid_t pid, int signum)
{
    int rc = kill(pid, signum);
    if (rc < 0)
    {
        unix_error("Kill error");
    }
}
    
void Pthread_detach(pthread_t tid)
{
    int rc = pthread_detach(tid);
    if (rc != 0)
    {
        posix_error(rc, "Pthread_detach error");
    }
}
    
struct hostent* Gethostbyname(const char* name)
{
    struct hostent* ptr = gethostbyname(name);
    if (ptr == NULL)
    {
        dns_error("Gethostbyname error");
    }
    return ptr;
}

pid_t Fork()
{
    pid_t pid = fork();
    if (pid < 0)
    {
        unix_error("Fork error");
    }
    return pid;
}