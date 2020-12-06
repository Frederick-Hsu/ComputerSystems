/* File name    : std_in_out.c
 * Description  : 
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
    char letter;
    while (read(STDIN_FILENO, &letter, 1) != 0)
    {
        write(STDOUT_FILENO, &letter, 1);
    }

    return 0;
}

