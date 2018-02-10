/*
 * cc ioctl.c && ./a.out
 */

#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <asm/byteorder.h>

struct ioctl_cmd {
	int cmd;
	unsigned int size;
#ifdef __LP64__
	unsigned char *buf;
#else

	#ifdef __LITTLE_ENDIAN_BITFIELD
	unsigned char *buf;
	unsigned int mbz;
	#elif __BIG_ENDIAN_BITFIELD
	unsigned int mbz;
	unsigned char *buf;
	#else
	#error "Please fix <asm/byteorder.h>"
	#endif /* ENDIAN_BITFIELD */
#endif /* __LP64__ */
	int flag;
	int dummy_pad;
};

int main(void)
{
	struct ioctl_cmd cmd;
	unsigned char data[128];
	unsigned long long laddr;

	memset(&cmd, 0, sizeof(cmd));
	cmd.buf = data;

#ifndef __LP64__
	memcpy(&laddr, &cmd.buf, sizeof(laddr));
	printf("laddr: %016llx\n", laddr);
	printf("cmd.buf: %p\n", cmd.buf);
#endif /* __LP64__ */

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
