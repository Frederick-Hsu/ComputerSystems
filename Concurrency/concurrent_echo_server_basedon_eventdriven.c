/* File name    : concurrent_echo_server_basedon_eventdriven.c
 * Description  : Build a echo-server driven by even, based on IO multiplexing.
 * Creator      : Frederique Hsu
 * 
 */


#include <stdio.h>
#include <stdlib.h>

#include <sys/select.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include "robust_io.h"
#include "net.h"

#define MAXLINE     0x4000

typedef struct                          /* Represents a pool of connected fd */
{
    int maxfd;                          /* Largest descriptor in read_set */
    fd_set read_set;                    /* Set of all active descriptors  */
    fd_set ready_set;                   /* Subset of descriptors ready for reading */
    int nready;                         /* Number of ready descriptors from select */
    int maxi;                           /* Highwater index into client array */
    int clientfd[FD_SETSIZE];           /* Set of active client descriptors */
    rio_t clientrio[FD_SETSIZE];        /* Set of active read buffers */
}
pool;

int byte_count = 0;     /* Counts total bytes received by server */

void init_pool(int listenfd, pool* p);
void add_client(int connfd, pool* p);
void check_clients(pool* p);

int main(int argc, char* argv[])
{
    int listenfd, connfd, port;
    socklen_t clientlen = sizeof(struct sockaddr_in);
    struct sockaddr_in clientaddr;

    static pool s_activeclient_pool;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <port>\n", argv[0]);
        exit(0);
    }
    port = strtol(argv[1], NULL, 10);

    listenfd = open_listenfd(port);
    init_pool(listenfd, &s_activeclient_pool);

    while (1)
    {
        /* wait for listening/connected descriptors to become ready */
        s_activeclient_pool.ready_set = s_activeclient_pool.read_set;

        /* select(...) function will always block, until at least one descriptor of readfd_set
         * is ready for reading.
         */
        s_activeclient_pool.nready = select(s_activeclient_pool.maxfd+1,
                                            &s_activeclient_pool.ready_set,
                                            NULL, NULL, NULL);
        
        /* If listening descriptor ready, add new client to pool */
        if (FD_ISSET(listenfd, &s_activeclient_pool.ready_set))
        {
            connfd = accept(listenfd, (struct sockaddr*)&clientaddr, &clientlen);
            add_client(connfd, &s_activeclient_pool);
        }
        /* Echo a text line from each ready connected descriptor */
        check_clients(&s_activeclient_pool);
    }

    return 0;
}

void init_pool(int listenfd, pool* p)
{
    /* Initially, there are no connected descriptors */
    p->maxi = -1;
    for (int index = 0; index < FD_SETSIZE; ++index)
    {
        p->clientfd[index] = -1;
    }

    /* Initially, listenfd is the only member of select readfd_set */
    p->maxfd = listenfd;
    FD_ZERO(&p->read_set);
    FD_SET(listenfd, &p->read_set);
}

void add_client(int connfd, pool* p)
{
    p->nready--;
    for (int i = 0; i < FD_SETSIZE; ++i)    /* Find an available slot */
    {
        if (p->clientfd[i] < 0)
        {
            /* Add the connected descriptor to the pool */
            p->clientfd[i] = connfd;
            rio_readinitb(&p->clientrio[i], connfd);

            /* Add the descriptor to the descriptor set */
            FD_SET(connfd, &p->read_set);
            /* Update max descriptor and pool highwater mark */
            if (connfd > p->maxfd)
            {
                p->maxfd = connfd;
            }
            if (i > p->maxi)
            {
                p->maxi = i;
            }
            break;
        }
        if (i == FD_SETSIZE)
        {
            fprintf(stderr, "add_client error: Too many clients.\n");
            exit(0);
        }
    }
}

void check_clients(pool* p)
{
    int connfd, n;
    char buf[MAXLINE];
    rio_t rio;

    for (int index = 0; ((index < p->maxi) && (p->nready > 0)); ++index)
    {
        connfd = p->clientfd[index];
        rio = p->clientrio[index];

        /* If the descriptor is ready, echo a text line from it */
        if ( (connfd > 0) && (FD_ISSET(connfd, &p->ready_set)) )
        {
            p->nready--;
            if ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0)
            {
                byte_count += n;

                printf("\n%s\n", buf);
                printf("Server received %d (%d total) bytes on fd %d\n", n, byte_count, connfd);
                
                rio_writen(connfd, buf, n);
            }
            else
            {
                /* EOF detected, remove descriptor from pool */
                close(connfd);
                FD_CLR(connfd, &p->read_set);
                p->clientfd[index]--;
            }
        }
    }
}