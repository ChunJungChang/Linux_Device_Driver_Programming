#include <linux/module.h>
#include <linux/init.h>

MODULE_LICENSE("Dual BSD/GPL");

static int sample_init(void)
{
    volatile int n = 0;

    printk("sample driver installed.\n");

    n++;
    printk("n %d\n", n);

    return 0;
}

static void sample_exit(void)
{
    printk("sample driver removed.\n");
}

module_init(sample_init);
module_exit(sample_exit);
