/* File name    : test_32_or_64_bit.c
 * Description  : To verify whether the program which you are building is 32-bit or 64-bit.
 * 
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
    int pointer_length = sizeof(void*);
    if (pointer_length == 4)     /* 4 bytes = 32bits */
    {
        printf("Your program runs in %d-bit mode.\n", pointer_length * 8);
    }
    else if (pointer_length == 8)   /* 8 bytes = 64bits */
    {
        printf("Your program runs in %d-bit mode.\n", pointer_length * 8);
    }
    
    return 0;
}