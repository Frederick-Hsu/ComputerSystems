#ifndef PROC_SIGNAL_H
#define PROC_SIGNAL_H

    typedef void handler_t(int signum);
    handler_t* Signal(int signum, handler_t* handler);

#endif  /* PROC_SIGNAL_H */