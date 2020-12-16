#ifndef TINY_H
#define TINY_H

    #include "robust_io.h"

    /* Deal with a HTTP transaction */
    void doit(int fd);

    /* Send the error message to client */
    void client_error(int fd, char* cause, char* errnum, char* shortmsg, char* longmsg);

    /* Read the request headers */
    void read_request_hdrs(rio_t* rp);

    /* Parse one HTML URI */
    int parse_uri(char* uri, char* filename, char* cgiargs);


#endif  /* TINY_H*/
