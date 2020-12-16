#include "tiny.h"
#include "server_contents.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dlfcn.h>
#include <assert.h>

const int MAXLINE = 0x4000;

void doit(int fd)
{
    int is_static;
    struct stat sbuf;
    char buf[MAXLINE], method[MAXLINE], uri[MAXLINE], version[MAXLINE];
    char filename[MAXLINE], cgi_args[MAXLINE];
    rio_t rio;

    void* librobustio_handler = dlopen("./librobustio.so", RTLD_LAZY);
    assert(librobustio_handler != NULL);

    void (*rio_readinitb)(rio_t* rp, int fd);
    rio_readinitb = dlsym(librobustio_handler, "rio_readinitb");
    assert(rio_readinitb != NULL);

    ssize_t (*rio_readlineb)(rio_t* rp, void* usrbuf, size_t maxlen);
    rio_readlineb = dlsym(librobustio_handler, "rio_readlineb");
    assert(rio_readlineb != NULL);
    
    /* Read request line and headers */
    rio_readinitb(&rio, fd);
    rio_readlineb(&rio, buf, MAXLINE);
    sscanf(buf, "%s %s %s", method, uri, version);

    if (strcasecmp(method, "GET"))
    {
        client_error(fd, method, "501", "Not Implemented", "Tiny_Web_Server does not implement this method.\n");
        return;
    }
    read_request_hdrs(&rio);

    /* Parse URI from GET request */
    is_static = parse_uri(uri, filename, cgi_args);

    /* Retrieve the meta information of "filename", and check whether it exists */
    if (stat(filename, &sbuf) != 0)
    {
        client_error(fd, filename, "404", "Not Found", "Tiny_Web_Server couldn't find this file.\n");
        return;
    }

    if (is_static)      /* Server static content */
    {
        /* Check whether the "filename" is a regular file and has owned the READ permission */
        if ( !((S_ISREG(sbuf.st_mode)) && (S_IRUSR & sbuf.st_mode)) )
        {
            client_error(fd, filename, "403", "Forbidden", "Tiny_Web_Server couldn't read the file.\n");
            return;
        }
        server_static(fd, filename, sbuf.st_size);;
    }
    else                /* Server dynamic content */
    {
        /* Check whether the "filename" is a regular file and has owned the EXECUTE permission */
        if ( !((S_ISREG(sbuf.st_mode)) && (S_IXUSR & sbuf.st_mode)) )
        {
            client_error(fd, filename, "403", "Forbidden", "Tiny_Web_Server couldn't run the CGI program.\n");
            return;
        }
        server_dynamic(fd, filename, cgi_args);
    }
    
    /* Close the librobustio_handler */
    assert(dlclose(librobustio_handler) == 0);
}

void client_error(int fd, char* cause, char* errnum, char* shortmsg, char* longmsg)
{
    char buf[MAXLINE], body[MAXLINE];

    /* Build the HTTP response body */
    sprintf(body, "<html><title>Tiny Error</title>");
    sprintf(body, "%s<body bgcolor=""FFFFFF"">\r\n", body);
    sprintf(body, "%s%s: %s\r\n", body, errnum, shortmsg);
    sprintf(body, "%s<p>%s: %s\r\n", body, longmsg, cause);
    sprintf(body, "%s<hr><em>The Tiny Web server</em>\r\n", body);

    /* Print out the HTTP response */
    sprintf(buf, "HTTP/1.0 %s %s\r\n", errnum, shortmsg);

    void* librobustio_handler = dlopen("./librobustio.so", RTLD_LAZY);
    assert(librobustio_handler != NULL);
    ssize_t (*rio_writen)(int fd, void* usrbuf, size_t);
    rio_writen = dlsym(librobustio_handler, "rio_writen");

    rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-type: text/html\r\n");
    rio_writen(fd, buf, strlen(buf));
    sprintf(buf, "Content-length: %d\r\n\r\n", (int)strlen(body));
    rio_writen(fd, buf, strlen(buf));
    rio_writen(fd, body, strlen(body));

    assert(dlclose(librobustio_handler) == 0);
}
    
void read_request_hdrs(rio_t* rp)
{
    char buf[MAXLINE];

    void* librobustio_handler = dlopen("./librobustio.so", RTLD_LAZY);
    assert(librobustio_handler != NULL);
    ssize_t (*rio_readlineb)(rio_t* rp, void* usrbuf, size_t maxlein);
    rio_readlineb = dlsym(librobustio_handler, "rio_readlineb");

    rio_readlineb(rp, buf, MAXLINE);
    while (strcmp(buf, "\r\n"))
    {
        rio_readlineb(rp, buf, MAXLINE);
        printf("%s", buf);
    }
    return;
}

int parse_uri(char* uri, char* filename, char* cgiargs)
{
    char* ptr;
    if (!strstr(uri, "cgi-bin"))    /* static content */
    {
        strcpy(cgiargs, "");
        strcpy(filename, ".");
        strcat(filename, uri);
        if (uri[strlen(uri)-1] == '/')
        {
            strcat(filename, "home.html");
        }
        return 1;
    }
    else        /* dynamic content */
    {
        ptr = index(uri, '?');
        if (ptr)
        {
            strcpy(cgiargs, ptr+1);
            *ptr = '\0';
        }
        else
        {
            strcpy(cgiargs, "");
        }
        strcpy(filename, ".");
        strcat(filename, uri);
        return 0;
    }
}
