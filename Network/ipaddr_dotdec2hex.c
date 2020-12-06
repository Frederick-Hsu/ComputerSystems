/* File name    : ipaddr_dotdec2hex.c
 * Description  : Convert the dot-and-decimal-number format of IP address into hex-format number.
 * Creator      : Frederique Hsu
 * Creation date: Sun.  06 Dec. 2020
 * Copyright(C) 2020    All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

unsigned int ipaddr_dotdec2hex(const char* dotdec_ipaddr);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "%s <dot-and-decimal-number IP address>", argv[1]);
        exit(1);
    }
    uint32_t ipaddr = ipaddr_dotdec2hex(argv[1]);
    printf("0x%08X\n", ipaddr);

    return 0;
}

unsigned int ipaddr_dotdec2hex(const char* dotdec_ipaddr)
{
    struct in_addr inaddr;
    inet_aton(dotdec_ipaddr, &inaddr);
    return ntohl(inaddr.s_addr);
}
