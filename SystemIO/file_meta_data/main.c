#include <stdio.h>

#include "file.h"

int main(int argc, char* argv[] /*, char* envp[] */)
{
    printf("Current program is %lu-bit.\n", sizeof(void*) * 8);

    query_file_info(argc, argv);
    query_file_descriptor_table();
    multi_procs_visit_shared_file();
    return 0;
}
