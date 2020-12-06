#include "with_buffer_robust_io.h"

#include <errno.h>
#include <string.h>

static ssize_t rio_read(rio_t* rp, char* usrbuf, size_t n);

void rio_readinitb(rio_t* rp, int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}

ssize_t rio_read(rio_t* rp, char* usrbuf, size_t n)
{
    int cnt;

    while (rp->rio_cnt <= 0)    /* Refill, if usrbuf is empty */
    {
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf, sizeof(rp->rio_buf));
        if (rp->rio_cnt < 0)
        {
            if (errno != EINTR)     /* Interrupted by sig handler return */
            {
                return -1;
            }
        }
        else if (rp->rio_cnt == 0)  /* EOF */
        {
            return 0;
        }
        else
        {
            rp->rio_bufptr = rp->rio_buf;
        }
    }

    /* Copy min(n, rp->rio_cnt) bytes from internal buf to user buf */
    cnt = n;
    if ((size_t)rp->rio_cnt < n)
    {
        cnt = rp->rio_cnt;
    }
    memcpy(usrbuf, rp->rio_bufptr, cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}

ssize_t rio_readlineb(rio_t* rp, void* usrbuf, size_t maxlen)
{
    int n, rc;
    char c, *bufp = usrbuf;

    for (n = 1; (size_t)n < maxlen; ++n)
    {
        if ((rc = rio_read(rp, &c, 1)) == 1)
        {
            *bufp++ = c;
            if (c == '\n')
            {
                break;
            }
        }
        else if (rc == 0)   /* EOF, no data read */
        {
            if (n == 1)
                return 0;
            else
                break;
        }
        else
        {
            return -1;
        }
    }
    *bufp = 0;
    return n;
}

ssize_t rio_readnb(rio_t* rp, void* usrbuf, size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char* bufp = usrbuf;

    while (nleft > 0)
    {
        if ((nread = rio_read(rp, bufp, nleft)) < 0)
        {
            if (errno == EINTR)
            {
                nread = 0;
            }
            else
            {
                return -1;
            }
        }
        else if (nread == 0)    /* EOF */
        {
            break;
        }
        nleft -= nread;
        bufp += nread;
    }
    return (n - nleft);
}
