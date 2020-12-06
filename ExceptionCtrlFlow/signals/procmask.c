#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void handler(int signum);
void initjobs(void);
void addjob(pid_t pid);
void deletejob(pid_t pid);


int main(int argc, char* argv[], char* envp[])
{
    int pid;
    sigset_t mask;

    signal(SIGCHLD, handler);
    initjobs();     /* Initialize the job list */

    while (1)
    {
        sigemptyset(&mask);
        sigaddset(&mask, SIGCHLD);
        sigprocmask(SIG_BLOCK, &mask, NULL);    /* Block the SIGCHLD */

        /* Produce the child process */
        if ((pid = fork()) == 0)
        {
            sigprocmask(SIG_UNBLOCK, &mask, NULL);      /* Unblock the SIGCHLD */
            execve("/bin/date", argv, NULL);
        }

        /* Parent process */
        addjob(pid);    /* Add the child to the job list */
        sigprocmask(SIG_UNBLOCK, &mask, NULL);      /* Unblock SIGCHLD */
    }
    exit(0);
}

void handler(int signum)
{
    pid_t pid;
    while ((pid = waitpid(-1, NULL, 0)) > 0)    /* Reap a zombie child process */
    {
        deletejob(pid);     /* Delete the child from the job list */
    }
    if (errno != ECHILD)
    {
        fprintf(stderr, "waitpid error: %s", strerror(errno));
        exit(errno);
    }
}

void initjobs(void)
{

}

void addjob(pid_t pid)
{

}

void deletejob(pid_t pid)
{

}