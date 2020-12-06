/* File name    : redirect.c
 * Description  : IO redirect from std-I/O to file.
 *
 */

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef int     file_descriptor;

int main(int argc, char* argv[])
{
    file_descriptor fd1, fd2;
    char letter;

    fd1 = open("foobar.txt", O_RDONLY, 0);
    fd2 = open("foobar.txt", O_RDONLY, 0);

    read(fd2, &letter, 1);
    dup2(fd2, fd1);         /* redirect fd1 to fd2 */
    read(fd1, &letter, 1);

    printf("letter = %c\n", letter);
    exit(0);
}