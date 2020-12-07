#include "net.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define LISTEN_QUEUE    1024

int open_clientfd(const char* server_ipaddr, int port)
{
    int clientfd;
    struct sockaddr_in servaddr;

    if ((clientfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(-1);
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    inet_aton(server_ipaddr, &servaddr.sin_addr);

    /* Establish a connection with the server */
    if (connect(clientfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(-1);
    }
    return clientfd;
}

int open_listenfd(unsigned int port)
{
    int listenfd;
    int sockopt = 1;
    struct sockaddr_in servaddr;

    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(-1);
    }

    /* Eliminate "address already in use" error from bind() function */
    if (0 != setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&sockopt, sizeof(sockopt)))
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(-1);
    }

    /* listenfd will be an endpoint for all requests for this server host,
     * on port and any IP address
     */
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);

    if (bind(listenfd, (const struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(-1);
    }

    /* Make it a listening socket, ready to accept the connection requests from clients */
    if (listen(listenfd, LISTEN_QUEUE) != 0)
    {
        fprintf(stderr, "Error: %s\n", strerror(errno));
        exit(-1);
    }
    return listenfd;
}
