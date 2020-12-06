#include "without_buffer_robust_io.h"

#include <errno.h>

    #define ARG_IN
    #define ARG_OUT

ssize_t rio_readn(ARG_IN file_descriptor fd, ARG_OUT void* usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char* pbuf = usrbuf;

    while (nleft > 0)
    {
        if ((nread = read(fd, pbuf, nleft)) < 0)
        {
            if (errno == EINTR)     /* Interrupted by sig. handler return */
            {
                nread = 0;          /* and call read() again */
            }
            else
            {
                return -1;          /* errno set by read() */
            }
        }
        else if (nread == 0)        /* EOF */
        {
            break;
        }
        nleft -= nread;
        pbuf += nread;
    }
    return (n - nleft);
}
    
ssize_t rio_writen(ARG_OUT file_descriptor fd, ARG_IN void* usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nwritten;
    char* pbuf = usrbuf;

    while (nleft > 0)
    {
        if ((nwritten = write(fd, pbuf, nleft)) <= 0)
        {
            if (errno == EINTR)
            {
                nwritten = 0;
            }
            else
            {
                return -1;
            }
        }
        nleft -= nwritten;
        pbuf += nwritten;
    }
    return n;
}
