#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <string.h>
#include <errno.h>


int main(int argc, char* argv[])
{
    void* lib_handler;

    void (*pctest1)(int*);
    void (*pctest2)(int*);
    int x;

    /* NOTE: here must specify the location of libctest.so 
     *       otherwise, dynamically loading will fail. 
     */
    lib_handler = dlopen("./libctest.so", RTLD_LAZY);   
    if (lib_handler == NULL)
    {
        fprintf(stderr, "Error : %s\n", dlerror());
        exit(1);
    }

    pctest1 = dlsym(lib_handler, "ctest1");
    if (pctest1 == NULL)
    {
        fprintf(stderr, "Error: %s\n", dlerror());
        exit(1);
    }

    pctest1(&x);
    printf("current x = %d\n", x);

    pctest2 = dlsym(lib_handler, "ctest2");
    if (pctest2 == NULL)
    {
        fprintf(stderr, "Error : %s\n", dlerror());
        exit(1);
    }
    pctest2(&x);
    printf("now x becomes : %d\n", x);

    dlclose(lib_handler);
    return 0;
}