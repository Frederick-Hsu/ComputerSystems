/* File     : fork_triple.c
 * Description  : Make the process forked 3 times.
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
    Fork();
    printf("Hello\n");
    exit(0);
}