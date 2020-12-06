/* File name    : shellex.c
 * Description  : Simulate the shell/bash routine
 * Creator      : Frederique Hsu
 * Creation date: Sat.  21 Nov. 2020
 * Copyright(C) 2020    All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../../liberror/errhandler.h"
#include "../../liberror/errwrapper.h"

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAXARGS     128
#define MAXLINE     0xFFFF

extern char** environ;

/* Function prototypes */
void eval(char* cmdline);
int parseline(char* buf, char** argv);
int builtin_command(char* argv[]);

int main(int argc, char* argv[], char* envp[])
{
    char cmdline[MAXLINE];

    while (1)
    {
        /* Read */
        printf("> ");
        fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin))
        {
            exit(0);
        }

        /* Evaluate */
        eval(cmdline);
    }
}

/* eval : Evaluate the command line */
void eval(char* cmdline)
{
    char* argv[MAXARGS];        /* Argument list execev() */
    char  buf[MAXLINE];         /* Holds modified command line */
    int bg;
    pid_t pid;

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if (argv[0] == NULL)
        return;     /* Ignore empty lines */

    if (!builtin_command(argv))
    {
        if ((pid = Fork()) == 0)    /* child process runs user job */
        {
            if (execve(argv[0], argv, environ) < 0)
            {
                printf("%s: Command not found.\n", argv[0]);
                exit(0);
            }
        }

        /* parent process waits for foreground job to terminate */
        if (!bg)
        {
            int status;
            if (waitpid(pid, &status, 0) < 0)
            {
                unix_error("waitfg: waitpid error");
            }
        }
        else
        {
            printf("%d %s", pid, cmdline);
        }
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
    if (!strcmp(argv[0], "quit"))   
    {
        exit(0);
    }
    if (!strcmp(argv[0], "&"))      /* Ignore singleton & */
    {
        return 1;
    }
    return 0;
}

/* parseline : Parse the command line and build the argv array */
int parseline(char* buf, char** argv)
{
    char* delim;    /* Points to first space delimiter */
    int argc;       /* Number of args */
    int bg;         /* Background job? */

    buf[strlen(buf) - 1] = ' ';     /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' '))   /* Ignore leading spaces */
    {
        buf++;
    }

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' ')))
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' '))
            buf++;
    }
    argv[argc] = NULL;

    /* Ignore blank lines */
    if (argc == 0)
    {
        return 1;
    }

    /* Should the job run in the background */
    if ((bg = (*argv[argc-1] == '&')) != 0)
    {
        argv[--argc] = NULL;
    }
    return bg;
}