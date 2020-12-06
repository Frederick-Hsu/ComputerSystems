#ifndef ERROR_WRAPPER_H
#define ERROR_WRAPPER_H

    #include <sys/types.h>
    #include <pthread.h>
    #include <sys/socket.h>

    pid_t Wait(int* status);
    void Kill(pid_t pid, int signum);
    void Pthread_detach(pthread_t tid);
    struct hostent* Gethostbyname(const char* name);
    pid_t Fork();

#endif  /* ERROR_WRAPPER_H */