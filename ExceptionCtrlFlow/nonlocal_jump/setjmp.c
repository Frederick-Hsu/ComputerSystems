/* File name    : setjmp.c
 * Description  : Demonstrate how the nonlocal-jump works
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <setjmp.h>

jmp_buf env;

int error1 = 0;
int error2 = 1;

void foo(void);
void bar(void);

int main(int argc, char* argv[], char* envp[])
{
    int rc = 0;

    setjmp(env);
    if (rc == 0)
    {
        foo();
    }
    else if (rc == 1)
    {
        printf("Detected an error1 condition in foo() function\n");
    }
    else if (rc == 2)
    {
        printf("Detected an error2 condition in foo() function\n");
    }
    else
    {
        printf("Unknown error condition in foo() function\n");
    }
    exit(0);
}

void foo(void)
{
    if (error1)
        longjmp(env, 1);
    bar();
}

void bar(void)
{
    if (error2)
        longjmp(env, 2);
}