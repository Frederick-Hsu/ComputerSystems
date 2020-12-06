/* File     : fork_twice.c
 * Description  : Make the process forked 2 times.
 * 
 */

#include "../liberror/errhandler.h"
#include "../liberror/errwrapper.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    Fork();
    Fork();
    printf("Hello\n");
    exit(0);
}