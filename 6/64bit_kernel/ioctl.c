/*
 * cc ioctl.c && ./a.out
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct ioctl_cmd {
	int cmd;
	unsigned int size;
	unsigned char *buf;
	int flag;
};

int main(void)
{
	/*
     * 32bit_kernel sizeof(struct ioctl_cmd): 16 
	 * 64bit_kernel sizeof(struct ioctl_cmd): 24
	 */

	printf("sizeof(struct ioctl_cmd) %d\n"
		    "    cmd = %d\n"
		    "    size = %d\n"
		    "    buf = %d\n"
		    "    flag = %d\n",
		    sizeof(struct ioctl_cmd),
		    offsetof(struct ioctl_cmd, cmd),
		    offsetof(struct ioctl_cmd, size),
		    offsetof(struct ioctl_cmd, buf),
		    offsetof(struct ioctl_cmd, flag));

	return 0;
}
