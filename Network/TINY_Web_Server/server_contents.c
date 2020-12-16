#include "server_contents.h"
#include "robust_io.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>

extern const int MAXLINE;
extern char** environ;

void server_static(int fd, char* filename, int filesize)
{
    int srcfd;
    char* srcp, filetype[MAXLINE], buf[MAXLINE];

    /* Send response header to client */
    get_filetype(filename, filetype);
    sprintf(buf, "HTTP/1.0 200 OK\r\n");
    sprintf(buf, "%sServer: Tiny Web Server\r\n", buf);
    sprintf(buf, "%sContent-length: %d\r\n", buf, filesize);
    sprintf(buf, "%sContent-type: %s\r\n\r\n", buf, filetype);

    void* librobustio_handler = dlopen("./librobustio.so", RTLD_LAZY);
    assert(librobustio_handler != NULL);
    ssize_t (*rio_writen)(file_descriptor fd, void* usrbuf, size_t n);
    rio_writen = dlsym(librobustio_handler, "rio-writen");
    rio_writen(fd, buf, strlen(buf));

    /* Send response body to client */
    srcfd = open(filename, O_RDONLY, 0);
    srcp = mmap(0, filesize, PROT_READ, MAP_PRIVATE, srcfd, 0);
    close(srcfd);
    rio_writen(fd, srcp, filesize);
    munmap(srcp, filesize);

    assert(dlclose(librobustio_handler) == 0);
}

void server_dynamic(int fd, char* filename, char* cgiargs)
{
    char buf[MAXLINE];
    char *emptylist[] = {NULL};

    /* Return first part of HTTP response */
    sprintf(buf, "HTTP/1.0 200 OK\r\n");

    void* librobustio_handler = dlopen("./librobustio.so", RTLD_LAZY);
    assert(librobustio_handler != NULL);
    ssize_t (*rio_writen)(file_descriptor fd, void* usrbuf, size_t n);;
    rio_writen = dlsym(librobustio_handler, "rio_writen");
    rio_writen(fd, buf, strlen(buf));

    sprintf(buf, "Server: Tiny Web Server\r\n");
    rio_writen(fd, buf, strlen(buf));

    if (fork() == 0)
    {
        /* Real server would st all CGI variables here */
        setenv("QUERY_STRING", cgiargs, 1);
        dup2(fd, STDOUT_FILENO);    /* Redirect stdout to client */
        execve(filename, emptylist, environ);   /* Run CGI program */
    }
    wait(NULL);     /* Parent waits for and reaps child process */

    assert(dlclose(librobustio_handler) == 0);
}

void get_filetype(char* filename, char* filetype)
{
    if (strstr(filename, ".html"))
        strcpy(filetype, "text/html");
    else if (strstr(filename, ".git"))
        strcpy(filetype, "image/gif");
    else if (strstr(filename, ".jpg"))
        strcpy(filetype, "imag/jpeg");
    else
        strcpy(filetype, "text/plain");
}
