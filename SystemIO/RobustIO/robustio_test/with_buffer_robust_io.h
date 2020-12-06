#ifndef WITH_BUFFER_ROBUST_IO_H
#define WITH_BUFFER_ROBUST_IO_H

    #include <unistd.h>

    #define RIO_BUFSIZE     8192
    
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

#endif  /* WITH_BUFFER_ROBUST_IO_H */