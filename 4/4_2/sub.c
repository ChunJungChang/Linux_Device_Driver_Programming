#include <linux/module.h>
#include <linux/init.h>

void sub(void)
{
	printk(KERN_ALERT "%s: sub() called\n", __func__);
}
