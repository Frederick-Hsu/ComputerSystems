/* File name    : echo_server.c
 * Description  : Build a server of network communication, used to communicate with client over the
 *              : ethernet for exchanging message.
 * Creator      : Frederique Hsu
 * Creation date: Mon.  07 Dec. 2020
 * Copyright(C) 2020    All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "net.h"
#include "robust_io.h"

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAXLINE     0X4000

void echo(int connfd);

int main(int argc, char* argv[])
{
    int listenfd, connfd, port, clientlen;

    struct sockaddr_in clientaddr;
    char* client_ipaddr;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[1]);
        exit(0);
    }

    port = strtol(argv[1], NULL, 10);
    listenfd = open_listenfd(port);

    while (1)
    {
        clientlen = sizeof(clientaddr);
        connfd = accept(listenfd, (struct sockaddr*)&clientaddr, (socklen_t*)&clientlen);
        client_ipaddr = inet_ntoa(clientaddr.sin_addr);
        printf("This server had connected to client(%s)\n", client_ipaddr);

        echo(connfd);
        close(connfd);
    }
    return 0;
}

void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    rio_readinitb(&rio, connfd);
    while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        printf("This server received %ld bytes\n", n);
        rio_writen(connfd, buf, n);
    }
}
