#ifndef WRAPPER_H
#define WRAPPER_H

    #include <sys/types.h>

    pid_t Fork(void);
    void Pause(void);
    void Kill(pid_t pid, int signum);   
    unsigned int Sleep(unsigned int seconds);

#endif  /* WRAPPER_H */