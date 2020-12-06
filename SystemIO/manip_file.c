/* File name    : manip_file.c
 * Description  : Learn how to manipulate the file by using Unix system IO APIs.
 * Creator      : Frederique Hsu
 * Creation date: Mon.  30 Nov. 2020
 * Copyright(C) 2020    All rights reserved.
 *
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define DEF_MODE    S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH
#define DEF_MASK    S_IWGRP | S_IWOTH

typedef int     file_descriptor;

int main(int argc, char* argv[])
{
    mode_t mode = umask(DEF_MASK);

    file_descriptor fd = open("foo.txt", O_CREAT | O_TRUNC | O_WRONLY, DEF_MODE);
    close(fd);

    file_descriptor fd2 = open("bar.txt", O_CREAT | O_RDONLY, S_IRUSR | S_IWUSR);
    printf("fd2 = %d\n", fd2);
    close(fd2);

    return 0;
}

