/* File name    : determine_stdc_version.c
 * Description  : Determine the standard version of C language.
 * Creator      : Frederique Hsu
 * Creation date: Fri.  11 Dec. 2020
 * Copyright(C) 2020    All rights reserved.
 * 
 */

#include <stdio.h>

int main(int argc, char* argv[])
{
    #if defined (__STDC_VERSION__)
        printf("__STDC_VERSION__ = %ld\n", __STDC_VERSION__);
    #endif

    #if defined (__STRICT_ANSI__)
        printf("__STRICT_ANSI__ = %d\n", __STRICT_ANSI__);
    #endif
    
    return 0;
}