/*
 * cc -S main.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
	volatile int n = 0;

    n++;
    printf("n %d\n", n);

	return 0;
}
