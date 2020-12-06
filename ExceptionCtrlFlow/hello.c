/* File name    : hello.c
 * Description  : Change the preliminary helloworld program to implement in another approach,
 *              : by using the syscall function write(....)
 * Creator      : Frederique Hsu
 * Creation date: Mon.  09 Nov. 2020
 * Copyright(C) 2020    All rights reserved.
 *
 */

#include <unistd.h>
#include <stdlib.h>

int main()
{
    write(1, "hello, world\n", 13);
    exit(0);
}