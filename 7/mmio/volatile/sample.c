/*
 * gcc -S -O2 sample.c
 */

#include <stdio.h>

int main(void)
{
    int val, n;
    int *p;

    val = 2008;
    p = &val;

    printf("%d\n", val);

    return 0;
}
