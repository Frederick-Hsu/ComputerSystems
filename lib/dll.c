/* File name    : dll.c
 * Description  : Demonstrate how to dynamically load the shared library.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int x[2] = {1, 2};
int y[2] = {3, 4};
int z[2];

int main()
{
    void* handle;
    void (*fnptr_addvec)(int*, int*, int*, int);
    char* error;

    /* Dynamically load shared library that contains addvec() function */
    handle = dlopen("./libvector.so", RTLD_LAZY);
    if (!handle)
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    /* Get a pointer to the addvec() function we just loaded */
    fnptr_addvec = dlsym(handle, "addvec");
    if ((error = dlerror()) != NULL)
    {
        fprintf(stderr, "%s\n", error);
        exit(1);
    }

    /* Now we can call addvec(), just like any other function */
    fnptr_addvec(x, y, z, 2);
    printf("z = {%d, %d}\n", z[0], z[1]);

    /* Unload the shared library */
    if (dlclose(handle) != 0)
    {
        fprintf(stderr, "%s\n", dlerror());
        exit(1);
    }

    return 0;
}