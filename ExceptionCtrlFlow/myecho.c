#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

unsigned int snooze(unsigned int secs);

int main(int argc, char* argv[], char* envp[])
{
    printf("Command line arguments: \n");
    for (int i = 0; argv[i] != NULL; ++i)
    {
        printf("\targv[%2d]: %s\n", i, argv[i]);
    }
    printf("\n");

    snooze(5);

    printf("Environment variables: \n");
    for (int index = 0; envp[index] != NULL; ++index)
    {
        printf("\tenvp[%2d]: %s\n", index, envp[index]);
    }

    return 0;
}

unsigned int snooze(unsigned int secs)
{
    unsigned int rc = sleep(secs);
    printf("Slept for %u of %u seconds.\n", secs - rc, secs);
    return rc;
}