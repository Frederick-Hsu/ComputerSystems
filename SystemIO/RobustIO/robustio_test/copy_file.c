#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "robust_io.h"

#define MAXLINE     (1024)

int main(int argc, char* argv[])
{
    int n;
    rio_t rio;
    char buf[MAXLINE];

    void* lib_handler;
    void (*rio_readinitb)(rio_t* rp, int fd);
    ssize_t (*rio_readlineb)(rio_t* rp, void* usrbuf, size_t maxlen);
    ssize_t (*rio_writen)(file_descriptor fd, void* usrbuf, size_t n);

    lib_handler = dlopen("./librobustio.so", RTLD_LAZY);
    if (lib_handler == NULL)
    {
        fprintf(stderr, "error: %s\n", dlerror());
        exit(1);
    }

    rio_readinitb = dlsym(lib_handler, "rio_readinitb");
    if (rio_readinitb == NULL)
    {
        fprintf(stderr, "error: %s\n", dlerror());
        exit(1);
    }
    rio_readlineb = dlsym(lib_handler, "rio_readlineb");
    rio_writen = dlsym(lib_handler, "rio_writen");

    rio_readinitb(&rio, STDIN_FILENO);
    while ((n = rio_readlineb(&rio, buf, MAXLINE)) != 0)
    {
        rio_writen(STDOUT_FILENO, buf, n);
    }

    if (dlclose(lib_handler) != 0)
    {
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(1);
    }
    return 0;
}
