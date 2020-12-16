/* File name    : concurrent_echo_server_basedon_Process.c
 * Description  : Make a concurrent echo_server, which handles the multi processes by virtue of process-forking mechanism.
 * Creator      : Frederique Hsu
 * Creation date: Wed.  16 Dec. 2020
 * Copyright(C) 2020    All rights reserved.
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <dlfcn.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>

void echo(int connfd);
void sigchld_handler(int signum);

int main(int argc, char* argv[])
{
    int listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = strtol(argv[1], NULL, 10);

    signal(SIGCHLD, sigchld_handler);

    void* libnet_handler = dlopen("./libnet.so", RTLD_LAZY);
    assert(libnet_handler != NULL);
    int (*open_listenfd)(unsigned int port);
    open_listenfd = dlsym(libnet_handler, "open_listenfd");
    listenfd = open_listenfd(port);

    while (1)
    {
        connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clientlen);
        if (fork() == 0)            /* Child process */
        {
            close(listenfd);        /* Child process closes its listening socket */
            echo(connfd);           /* Child process serves the client request */
            close(connfd);          /* Child process closes connection with client */
            exit(0);                /* Child process terminates */
        }
        close(connfd);              /* Parent process closes the connected socket fd */
    }

    assert(dlclose(libnet_handler) == 0);
    return 0;
}

void echo(int connfd)
{

}

void sigchld_handler(int signum)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
    {
        ;
    }
    return;
}
