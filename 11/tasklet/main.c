#include <linux/module.h>
#include <linux/init.h>
#include <linux/interrupt.h>

MODULE_LICENSE("Dual BSD/GPL");

/*
 * cat /proc/interrupts
 * 9:      15293    XT-PIC  acpi, enp0s3
 * enp0s3 is network card ISR
 */
const int IRQ_NUM = 9;
void *irq_dev_id = (void *)&IRQ_NUM;
struct tasklet_struct tasklet;

void sample_tasklet(unsigned long data) {
    printk("%s called (%ld, %ld, %ld)\n",
            __func__, in_irq(), in_softirq(), in_interrupt());
}

static irqreturn_t sample_isr(int irq, void *dev_instance)
{
    if (printk_ratelimit()) {
        printk("%s irq %d dev_instance %p \n", __func__, irq, dev_instance);
        
        tasklet_schedule(&tasklet);
    }

    return IRQ_NONE;
}

static int sample_init(void)
{
    int ret = 0;

    printk("sample driver installed.\n");

    tasklet_init(&tasklet, sample_tasklet, 0);

    ret = request_irq(IRQ_NUM,
                    sample_isr,
                    IRQF_SHARED,
                    "sample",
                    irq_dev_id);

    if (ret) {
        printk("request_irq() failed (%d)\n", ret);
        tasklet_kill(&tasklet);
        goto out;
    }

out:
    return ret;
}

static void sample_exit(void)
{
    printk("sample driver removed.\n");

    tasklet_kill(&tasklet);
    free_irq(IRQ_NUM, irq_dev_id);
}

module_init(sample_init);
module_exit(sample_exit);
