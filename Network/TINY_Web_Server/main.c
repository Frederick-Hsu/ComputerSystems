/* Project name : TINY_Web_Server
 * Description  : A simple, iterative HTTP/1.0 Web server that uses the GET method to serve
 *              : static and dynamic content.
 * ================================================================================================
 * File name    : main.c
 * Description  : This file implements the main() entry function for current project.
 * Creator      : Frederique Hsu
 * Creation date: Fri.  11 Dec. 2020
 * Copyright(C) 2020    All rights reserved.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <unistd.h>
#include <dlfcn.h>
#include <arpa/inet.h>

#include "tiny.h"

int main(int argc, char* argv[])
{
    printf("Current program is %ld-bit.\n", sizeof(void*) * 8);
    printf("Current C standard no. = %ld\n", __STDC_VERSION__);

    typedef int     file_descriptor;
    file_descriptor listenfd, connfd;

    int port, clientlen;
    struct sockaddr_in clientaddr;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }

    void* libnet_handler = dlopen("./libnet.so", RTLD_LAZY);
    assert(libnet_handler != NULL);

    int (*open_listenfd)(unsigned int port);
    open_listenfd = (int *)dlsym(libnet_handler, "open_listenfd");
    assert(open_listenfd != NULL);

    port = strtol(argv[1], NULL, 10);
    listenfd = open_listenfd(port);

    while (1)
    {
        clientlen = sizeof(clientaddr);
        connfd = accept(listenfd, (struct sockaddr*)&clientaddr, (socklen_t*)&clientlen);
        doit(connfd);
        close(connfd);
    }

    if (libnet_handler)
    {
        assert(dlclose(libnet_handler) == 0);
    }

    return 0;
}