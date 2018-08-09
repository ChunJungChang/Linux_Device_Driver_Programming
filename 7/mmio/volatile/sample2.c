/*
 * gcc -S -O2 sample2.c
 */

#include <stdio.h>

int main(void)
{
    int val, n;
    int *p;
    //volatile int *p;

    val = 2008;
    p = &val;

    n = *p;
    n = *p;
    n = *p;

    printf("%d\n", n);

    return 0;
}
