/* File name    : mulvec.c
 * Description  : vector multiplying method.
 *
 */

#include "vector.h"

void mulvec(int* x, int* y, int* z, int n)
{
    int i;
    for (i = 0; i < n; ++i)
    {
        z[i] = x[i] * y[i];
    }
}