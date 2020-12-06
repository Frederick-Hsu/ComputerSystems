#ifndef WITHOUT_BUFFER_ROBUST_IO_H
#define WITHOUT_BUFFER_ROBUST_IO_H

    #include <unistd.h>

    typedef int     file_descriptor;
    ssize_t rio_readn(file_descriptor fd, void* usrbuf, size_t n);
    ssize_t rio_writen(file_descriptor fd, void* usrbuf, size_t n);


#endif  /* WITHOUT_BUFFER_ROBUST_IO_H */