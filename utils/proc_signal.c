#include "proc_signal.h"
#include "errhandler.h"

#include <stdlib.h>
#include <signal.h>

#if 1

    handler_t* Signal(int signum, handler_t* handler)
    {
        struct sigaction action, old_action;

        action.sa_handler = handler;
        sigemptyset(&action.sa_mask);   /* Block sigs of type being handled */
        action.sa_flags = SA_RESTART;   /* Restart syscalls, if possible */

        if (sigaction(signum, &action, &old_action) < 0)
        {
            unix_error("Signal error");
        }
        return (old_action.sa_handler);
    }
#endif