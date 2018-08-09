#include <linux/module.h>
#include <linux/init.h>
#include <linux/mii.h>

MODULE_LICENSE("Dual BSD/GPL");

void external_sub(void) __attribute__ ((unused));

void external_(void)
{
	mii_link_ok(NULL);
}

static int hello_init(void)
{
	printk(KERN_ALERT "hello driver loaded\n");

	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "hello driver unloaded\n");
}

module_init(hello_init);
module_exit(hello_exit);
