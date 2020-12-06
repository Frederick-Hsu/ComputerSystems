#include "file.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

void query_file_info(int argc, char* argv[])
{
    struct stat file_stat;
    char* type, *readok;

    stat(argv[1], &file_stat);
    if (S_ISREG(file_stat.st_mode))     /* Determine the file type */
    {
        type = "regular file";
    }
    else if (S_ISDIR(file_stat.st_mode))
    {
        type = "directory";
    }
    else if (S_ISSOCK(file_stat.st_mode))
    {
        type = "socket";
    }
    else if (S_ISLNK(file_stat.st_mode))
    {
        type = "symbol link";
    }
    else if (S_ISFIFO(file_stat.st_mode))
    {
        type = "FIFO/pipe";
    }
    else if (S_ISBLK(file_stat.st_mode))
    {
        type = "block device";
    }
    else if (S_ISCHR(file_stat.st_mode))
    {
        type = "character device";
    }
    else
    {
        type = "unknown";
    }

    if (file_stat.st_mode & S_IRUSR)
    {
        readok = "yes";
    }
    else
    {
        readok = "no";
    }
    printf("This \"%s\" is %s, its readable: %s\n", argv[1], type, readok);
}

void query_file_descriptor_table(void)
{
    int fd1, fd2;
    char letter;

    fd1 = open("foobar.txt", O_CREAT | O_RDONLY, 0);
    fd2 = open("foobar.txt", O_RDONLY, 0);

    read(fd1, &letter, 1);
    printf("letter = %c\n", letter);

    read(fd2, &letter, 1);
    printf("letter = %c\n", letter);
}

void multi_procs_visit_shared_file(void)
{
    int fd;
    char letter;
    char* filename = "foobar.txt";

    fd = open(filename, O_RDONLY, 0);
    if (fork() == 0)
    {
        read(fd, &letter, 1);
        printf("child process visits file(\"%s\"), get character: %c\n", filename, letter);
        write(fd, "Child\n", strlen("Child\n")+1);
        exit(0);
    }

    wait(NULL);
    read(fd, &letter, 1);
    printf("parent process visits file(\"%s\"), get character: %c\n", filename, letter);

    write(fd, "Parent\n", strlen("Parent\n")+1);
    exit(0);
}
