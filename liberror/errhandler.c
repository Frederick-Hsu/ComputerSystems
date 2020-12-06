#include "errhandler.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <netdb.h>
#include <sys/socket.h>
extern int h_errno;

void unix_error(char* msg)      /* Unix-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(errno);
}

void posix_error(int code, char* msg)   /* POSIX-style error */
{
    fprintf(stderr, "%s: %s\n", msg, strerror(code));
    exit(code);
}    

void dns_error(char* msg)       /* DNS-style error */
{
    fprintf(stderr, "%s: DNS error %d\n", msg, h_errno);
}

void app_error(char* msg)       /* Application error */
{
    fprintf(stderr, "%s\n", msg);
    exit(0);
}