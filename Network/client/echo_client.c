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

#include "robust_io.h"
#include "net.h"

#define MAXLINE     0x4000

int main(int argc, char* argv[], char* envp[])
{
    int clientfd, port;
    char* server_ipaddr;
    char buf[MAXLINE];
    rio_t rio;

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <server_ipaddr> <port_number>", argv[0]);
        exit(0);
    }
    server_ipaddr = argv[1];
    port = strtol(argv[2], NULL, 10);

    clientfd = open_clientfd(server_ipaddr, port);
    rio_readinitb(&rio, clientfd);

    while (fgets(buf, MAXLINE, stdin) != NULL)
    {
        rio_writen(clientfd, buf, strlen(buf));
        rio_readlineb(&rio, buf, MAXLINE);
        fputs(buf, stdout);
    }
    close(clientfd);

    return 0;
}
