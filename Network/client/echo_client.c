/* File name    : echo_client.c
 * Description  : Build a client of network communication, used to send message to server side,
 *              : and receive the message from server, print out these echoed message.
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

#include "robust_io.h"
#include "net.h"

#define MAXLINE     0x4000

int main(int argc, char* argv[], char* envp[])
{
    int clientfd, port;
    char* server_ipaddr;
    char buf[MAXLINE];
    rio_t rio;

    int (*open_clientfd)(const char* server_ipaddr, int port);
    ssize_t (*rio_readinitb)(rio_t* rp, int fd);
    ssize_t (*rio_writen)(file_descriptor fd, void* userbuf, size_t n);
    ssize_t (*rio_readlineb)(rio_t* rp, void* userbuf, size_t maxlen);

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <server_ipaddr> <port_number>", argv[0]);
        exit(0);
    }
    server_ipaddr = argv[1];
    port = strtol(argv[2], NULL, 10);

    void* libnet_handler = dlopen("./libnet.so", RTLD_LAZY);
    assert(libnet_handler != NULL);

    void* librobustio_handler = dlopen("./librobustio.so", RTLD_LAZY);
    assert(librobustio_handler != NULL);

    open_clientfd = dlsym(libnet_handler, "open_clientfd");
    assert(open_clientfd != NULL);
    rio_readinitb = dlsym(librobustio_handler, "rio_readinitb");
    assert(rio_readinitb != NULL);
    rio_writen = dlsym(librobustio_handler, "rio_writen");
    assert(rio_writen != NULL);
    rio_readlineb = dlsym(librobustio_handler, "rio_readlineb");
    assert(rio_readlineb != NULL);

    clientfd = open_clientfd(server_ipaddr, port);
    rio_readinitb(&rio, clientfd);

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        rio_writen(clientfd, buf, strlen(buf));
        rio_readlineb(&rio, buf, MAXLINE);
        fputs(buf, stdout);
    }
    close(clientfd);

    assert(dlclose(libnet_handler) == 0);
    assert(dlclose(librobustio_handler) == 0);

    return 0;
}
