/*  File name   : concurrent_echo_client.c
 * Description  : Communicate with echo_server concurrently.
 * Creator      : Frederique Hsu
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <arpa/inet.h>

#include "net.h"
#include "robust_io.h"

#define MAXLINE     0x4000

int main(int argc, char* argv[])
{
    int clientfd, port;
    char* server_ipaddr;
    char buf[MAXLINE];
    rio_t rio;

    if (argc != 3)
    {
        fprintf(stderr, "usage: %s <server_ipaddr> <port>\n", argv[0]);
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