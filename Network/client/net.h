#ifndef NET_H
#define NET_H

    int open_clientfd(const char* server_ipaddr, int port);
    int open_listenfd(unsigned int port);


#endif  /* NET_H */
