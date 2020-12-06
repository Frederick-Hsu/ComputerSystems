#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("Current system is %ld-bit\n", sizeof(void*) * 8);
    return 0;
}