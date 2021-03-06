/* File name    : concurrent_echo_server_basedon_select.c
 * Description  : By using the IO multiplexing, echo server adopts the select() to wait
 *              : and listen on both the connection request and stdin inputing.
 * Creator      : Frederique Hsu
 * Creation date: Wed.  16 Dec. 2020
 * Copyright(C) 2020    All rights reserved.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <dlfcn.h>
#include <sys/select.h>

#include "net.h"
#include "robust_io.h"

#define MAXLINE     0X4000

void echo(int connfd);
void command(void);

int main(int argc, char* argv[])
{
    int listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;

    fd_set read_fdset, ready_fdset;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = strtol(argv[1], NULL, 10);

    void* libnet_header = dlopen("./libnet.so", RTLD_LAZY);
    assert(libnet_header != NULL);
    int (*open_listenfd)(unsigned int port);
    open_listenfd = dlsym(libnet_header, "open_listenfd");
    listenfd = open_listenfd(port);

    FD_ZERO(&read_fdset);                   /* Clear read fd set */
    FD_SET(STDIN_FILENO, &read_fdset);      /* Add stdin into the read fd set */
    FD_SET(listenfd, &read_fdset);          /* Add listenfd into the read fd set */

    while (1)
    {
        ready_fdset = read_fdset;
        select(listenfd+1, &read_fdset, NULL, NULL, NULL);
        if (FD_ISSET(STDIN_FILENO, &ready_fdset))
        {
            command();      /* Read command line from stdin */
        }
        if (FD_ISSET(listenfd, &ready_fdset))
        {
            connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clientlen);
            echo(connfd);   /* Echo client input until EOF */
            close(connfd);
        }
    }

    assert(dlclose(libnet_header) == 0);
    return 0;
}

void command(void)
{
    char buf[MAXLINE];
    if (!fgets(buf, MAXLINE, stdin))
    {
        exit(0);
    }
    printf("%s\n", buf);
}

void echo(int connfd)
{
    size_t n;
    char buf[MAXLINE];
    rio_t rio;

    void* librobustio_handler = dlopen("./librobustio.so", RTLD_LAZY);
    assert(librobustio_handler != NULL);
    void (*rio_readinitb)(rio_t* rp, int fd);
    rio_readinitb = dlsym(librobustio_handler, "rio_readinitb");
    assert(rio_readinitb != NULL);
    rio_readinitb(&rio, connfd);

    ssize_t (*rio_readlineb)(file_descriptor fd, void* userbuf, size_t n);
    rio_readlineb = dlsym(librobustio_handler, "rio_readlineb");
    assert(rio_readlineb != NULL);

    ssize_t (*rio_writen)(file_descriptor fd, void* userbuf, size_t n);
    rio_writen = dlsym(librobustio_handler, "rio_writen");
    assert(rio_writen != NULL);

    while ((n = rio_readlineb(connfd, buf, MAXLINE)) != 0)
    {
        printf("server received %ld bytes.\n", n);
        rio_writen(connfd, buf, MAXLINE);
    }
    assert(dlclose(librobustio_handler) == 0);
}
