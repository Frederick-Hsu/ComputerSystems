/* File name    : hostinfo.c
 * Description  : Retrieve the host entry according to domain name of IP address.
 *
 */


#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

int main(int argc, char* argv[])
{
    char** pp;
    struct in_addr addr;
    struct hostent *hostp;

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <domain name or dotted-decimal IP address>\n", argv[1]);
        exit(1);
    }

    if (inet_aton(argv[1], &addr) == 0)
    {
        fprintf(stderr, "Error: Failed to convert hostname to inet_addr.\n");
        exit(2);
    }
    hostp = gethostbyaddr((const char*)&addr, sizeof(addr), AF_INET);
    printf("Official host name: %s\n", hostp->h_name);

    for (pp = hostp->h_aliases; *pp != NULL; ++pp)
    {
        printf("Doname name alias: %s\n", *pp);
    }
    for (pp = hostp->h_addr_list; *pp != NULL; ++pp)
    {
        addr.s_addr = ((struct in_addr*)*pp)->s_addr;
        printf("Name server address: %s\n", inet_ntoa(addr));
    }

    return 0;
}
