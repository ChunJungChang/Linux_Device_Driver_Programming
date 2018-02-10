/*
 * devone.c for sleep
 */

#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL");

#define DRIVER_NAME "devone"

static int devone_devs = 1;
static int devone_major = 0;
static struct cdev devone_cdev;

char flag = 'n';
EXPORT_SYMBOL(flag);

wait_queue_head_t yutaka_sample_wait;
EXPORT_SYMBOL(yutaka_sample_wait);

ssize_t devone_read(struct file *filp, char __user *buf, size_t count,
                    loff_t *f_pos)
{
    int i;
    unsigned char val = 0xff;
    int retval;

    init_waitqueue_head(&yutaka_sample_wait);
    /* 
     * Kernel 2.6.23.1
     * sleep_on(&yutaka_sample_wait);
     */
    wait_event(yutaka_sample_wait, flag != 'n');

    printk("Wakeup! (%s)\n", __func__);

    for (i = 0;i < count;i++) {
        if (copy_to_user(&buf[i], &val, 1)) {
            retval = -EFAULT;
            goto out;
        }
    }
    retval = count;

out:
    return (retval);
}

struct file_operations devone_fops = {
    .read = devone_read,
};

static int devone_init(void)
{
    dev_t dev = MKDEV(devone_major, 0);
    int alloc_ret = 0;
    int major;
    int cdev_err = 0;

    alloc_ret = alloc_chrdev_region(&dev, 0, devone_devs, DRIVER_NAME);
    if (alloc_ret)
        goto error;
    devone_major = major = MAJOR(dev);

    cdev_init(&devone_cdev, &devone_fops);
    devone_cdev.owner = THIS_MODULE;

    cdev_err = cdev_add(&devone_cdev, MKDEV(devone_major, 0), devone_devs);
    if (cdev_err)
        goto error;

    printk(KERN_ALERT "%s driver(major %d) installed.\n", DRIVER_NAME, major);

    return 0;

error:
    if (cdev_err == 0)
        cdev_del(&devone_cdev);

    if (alloc_ret == 0)
        unregister_chrdev_region(dev, devone_devs);

    return -1;

}

static void devone_exit(void)
{
    dev_t dev = MKDEV(devone_major, 0);
    cdev_del(&devone_cdev);
    unregister_chrdev_region(dev, devone_devs);

    printk(KERN_ALERT "%s driver removed.\n", DRIVER_NAME);
}

module_init(devone_init);
module_exit(devone_exit);
