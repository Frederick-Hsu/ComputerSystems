/* File name    : ipaddr_hex2dotdec.c
 * Description  : Convert the hex-format number into dot-and-decimal-number format IP address.
 * Creator      : Frederique Hsu
 * Creation date: Sun.  06 Dec. 2020
 * Copyright(C) 2020    All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <arpa/inet.h>

char* ipaddr_hex2dotdec(in_addr_t hex_ipaddr);

int main(int argc, char* argv[])
{
    unsigned int addr;          /* address in host byte order */

    if (argc != 2)
    {
        fprintf(stderr, "usage: %s <hex-format number>\n", argv[1]);
        exit(1);
    }
    sscanf(argv[1], "%X", &addr);
    printf("%s\n", ipaddr_hex2dotdec(addr));

    return 0;
}

char* ipaddr_hex2dotdec(in_addr_t hex_ipaddr)
{
    struct in_addr inaddr;
    inaddr.s_addr = htonl(hex_ipaddr);
    return inet_ntoa(inaddr);
}
