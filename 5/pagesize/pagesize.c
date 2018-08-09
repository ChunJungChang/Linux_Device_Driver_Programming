#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <i386-linux-gnu/sys/user.h>

int main(void)
{
	void *ptr, *palign;

	printf("PAGE_SIZE: %lu\n", PAGE_SIZE);
	palign = (void*)(((unsigned long)ptr + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1));
	printf("palign: %p\n", palign);

	return 0;
}
