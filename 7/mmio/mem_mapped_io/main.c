#include <linux/module.h>
#include <linux/init.h>
#include <asm/io.h>

MODULE_LICENSE("Dual BSD/GPL");

#define SAMPLE_REG_ADD 0xFEC00000

static int sample_init(void)
{
    struct resource *pos = NULL;
    char *reg;

    printk("sample driver installed.\n");

    pos = request_mem_region(SAMPLE_REG_ADD, 1024, "sample");
    if (pos) {
        /*
         * The driver name, Sample, does not show in /proc/iomem
         * I do not know why
         */
        printk("request_mem_region %s\n", pos->name);

        reg = ioremap_nocache(SAMPLE_REG_ADD, 1024);
        if (reg != NULL) {
            printk("phy = %x, vir = %x\n", SAMPLE_REG_ADD, *reg);
            iounmap(reg);
            release_mem_region(SAMPLE_REG_ADD, 1024);
        }
    } else {
        printk("request_mem_region failed\n");
    }

    return 0;
}

static void sample_exit(void)
{
    printk("sample driver removed.\n");
}

module_init(sample_init);
module_exit(sample_exit);
