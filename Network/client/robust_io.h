#ifndef ROBUST_IO_H
#define ROBUST_IO_H

    #include <unistd.h>

    #define RIO_BUFSIZE     8192

    #define ARG_IN
    #define ARG_OUT

    typedef struct rio
    {
        int rio_fd;                     /* Descriptor for this internal buf */
        int rio_cnt;                    /* Unread bytes in internal buffer */
        char* rio_bufptr;               /* Next unread byte in internal buf */
        char rio_buf[RIO_BUFSIZE];      /* Internal buffer */
    }
    rio_t;

    void rio_readinitb(rio_t* rp, int fd);
    ssize_t rio_readlineb(rio_t* rp, void* usrbuf, size_t maxlen);
    ssize_t rio_readnb(rio_t* rp, void* usrbuf, size_t n);

/*================================================================================================*/

    typedef int     file_descriptor;
    ssize_t rio_readn(ARG_IN file_descriptor fd, ARG_OUT void* usrbuf, size_t n);
    ssize_t rio_writen(ARG_OUT file_descriptor fd, ARG_IN void* usrbuf, size_t n);


#endif  /* ROBUST_IO_H */
