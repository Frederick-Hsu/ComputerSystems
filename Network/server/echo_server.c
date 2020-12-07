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
#include <dlfcn.h>
#include <assert.h>

#include "net.h"
#include "robust_io.h"

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define MAXLINE     0X4000

void echo(int connfd);

static void* libnet_handler;
static void* librobustio_handler;

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
    libnet_handler = dlopen("./libnet.so", RTLD_LAZY);
    assert(libnet_handler != NULL);
    librobustio_handler = dlopen("./librobustio.so", RTLD_LAZY);
    assert(librobustio_handler != NULL);

    int (*open_listenfd)(unsigned int port);
    open_listenfd = dlsym(libnet_handler, "open_listenfd");

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

    assert(dlclose(libnet_handler) == 0);
    assert(dlclose(librobustio_handler) == 0);
    return 0;
}

void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    void (*rio_readinitb)(rio_t* rp, int fd);
    ssize_t (*rio_readlineb)(rio_t* rp, void* userbuf, size_t maxlen);
    ssize_t (*rio_writen)(file_descriptor fd, void* userbuf, size_t n);

    rio_readinitb = dlsym(librobustio_handler, "rio_readinitb");
    assert(rio_readinitb != NULL);
    rio_readlineb = dlsym(librobustio_handler, "rio_readlineb");
    assert(rio_readlineb != NULL);
    rio_writen = dlsym(librobustio_handler, "rio_writen");
    assert(rio_writen != NULL);

    rio_readinitb(&rio, connfd);
    while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        printf("This server received %ld bytes\n", n);
        rio_writen(connfd, buf, n);
    }
}
