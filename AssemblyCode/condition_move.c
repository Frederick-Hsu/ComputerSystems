#include "condition_move.h"

int absdiff(int x, int y)
{
    return ((x < y) ? (y - x) : (x - y));
}

int cmovdiff(int x, int y)
{
    int tval = y - x;
    int rval = x - y;
    int test = x < y;
    if (test)
        rval = tval;
    return rval;
}

int cread(int *xp)
{
    return (xp ? *xp : 0);
}

int lcount = 0;
int absdiff_se(int x, int y)
{
    return (x < y) ? (lcount++, y-x) : (x-y);
}