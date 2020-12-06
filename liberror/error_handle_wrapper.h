#ifndef ERROR_HANDLE_WRAPPER_H
#define ERROR_HANDLE_WRAPPER_H

    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <errno.h>

    #if 0
    /* Unix-style error handling */
    #include <sys/types.h>
    #include <sys/wait.h>
    
    if ((pid = wait(NULL)) < 0)
    {
        fprintf(stderr, "wait error: %s\n", strerror(errno));
        exit(errno);
    }

    /*=============================================================================================*/

    /* POSIX-style error handling */
    #incldue <pthread.h>

    if ( (retcode = pthread_create(&tid, NULL, thread, NULL)) != 0 )
    {
        fprintf(stderr, "pthread_create error: %s\n", strerror(retcode));
        exit(retcode);
    }


    /*=============================================================================================*/

    /* DNS-style error handling */
    #include <netdb.h>
    #include <sys/socket.h>
    extern int h_errno;

    if ((p = gethostbyname(name)) == NULL)
    {
        fprintf(stderr, "gethostbyname error: %s\n", hstrerror(h_errno));
        exit(h_errno);
    }
    #endif

#endif  /* ERROR_HANDLE_WRAPPER_H */