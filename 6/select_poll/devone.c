#include <linux/init.h>
#include <linux/module.h>
#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/poll.h>
#include <asm/uaccess.h>
#include <asm/errno.h>
#include <asm-generic/errno-base.h>
#include <linux/slab.h>
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL");

static unsigned int timeout_value = 10;
module_param(timeout_value, uint, 0);

static int devone_devs = 1;
static int devone_major = 0;
static int devone_minor = 0;
static struct cdev devone_cdev;
static struct class *devone_class = NULL;
static dev_t devone_dev;

struct devone_data {
	struct timer_list timeout;
	spinlock_t lock;
	wait_queue_head_t read_wait;
	int timeout_done;
	struct semaphore sem;
};

static void devone_timeout(unsigned long arg)
{
	struct devone_data *dev = (struct devone_data *)arg;
	unsigned long flags;

	printk("%s called\n", __func__);

	spin_lock_irqsave(&dev->lock, flags);

	dev->timeout_done = 1;
	wake_up_interruptible(&dev->read_wait);

	spin_unlock_irqrestore(&dev->lock, flags);
}

unsigned int devone_poll(struct file *filp, poll_table *wait)
{
	struct devone_data *dev = filp->private_data;
	unsigned int mask = POLLOUT | POLLWRNORM;

	printk("%s called\n", __func__);

	if (dev == NULL)
		return -EBADFD;

	down(&dev->sem);
	/* Go to sleep and function devone_timeout will wake it up */
	poll_wait(filp, &dev->read_wait, wait);
	if (dev->timeout_done == 1) {
		mask |= POLLIN | POLLRDNORM;
	}
	up(&dev->sem);

	printk("%s returned (mask 0x%x)\n", __func__, mask);
	return (mask);
}

ssize_t devone_write(struct file *filp, const char __user *buf, size_t count, loff_t *f_pos)
{
	return -EFAULT;
}

ssize_t devone_read(struct file *filp, char __user *buf, size_t count, loff_t *f_pos)
{
	struct devone_data *dev = filp->private_data;
	int i;
	unsigned char val;
	int retval;

	/* Critical section, get semaphore */
	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	if (dev->timeout_done == 0) { /* no read */
		/* Critical section, release semaphore */
		up(&dev->sem);
		if (filp->f_flags & O_NONBLOCK) /* Non-blocking mode */
			return -EAGAIN;
		do {
			retval = wait_event_interruptible_timeout(
					dev->read_wait,
					dev->timeout_done == 1, 1*HZ);
			if (retval == -ERESTARTSYS)
				return -ERESTARTSYS;
		} while (retval == 0); /* Timeout elapsed */

        /* Critical section, get semaphore */
		if (down_interruptible(&dev->sem))
			return -ERESTARTSYS;
	}

	val = 0xff;
	for (i = 0 ; i < count ; i++) {
		if (copy_to_user(&buf[i], &val, 1)) {
			retval = -EFAULT;
			goto out;
		}
	}
	retval = count;

out:
	dev->timeout_done = 0;
	/* Restart timer */
	mod_timer(&dev->timeout, jiffies + timeout_value*HZ);

    /* Critical section, release semaphore */
	up(&dev->sem);

	return (retval);
}

int devone_close(struct inode *inode, struct file *filp)
{
	struct devone_data *dev = filp->private_data;

	if (dev) {
		del_timer_sync(&dev->timeout);
		kfree(dev);
	}

	return 0;
}

int devone_open(struct inode *inode, struct file *filp)
{
	struct devone_data *dev;

	dev = kmalloc(sizeof(struct devone_data), GFP_KERNEL);
	if (dev == NULL) {
		return -ENOMEM;
	}

	/* Initialize members */
	spin_lock_init(&dev->lock);

	init_waitqueue_head(&dev->read_wait);

	sema_init(&dev->sem, 1);

	init_timer(&dev->timeout);
	dev->timeout.function = devone_timeout;
	dev->timeout.data = (unsigned long)dev;

	filp->private_data = dev;

	/* Start timer */
	dev->timeout_done = 0;
	/* Modify expire of timer for many applications */
	mod_timer(&dev->timeout, jiffies + timeout_value*HZ);

	return 0;
}

struct file_operations devone_fops = {
	.owner = THIS_MODULE,
	.open = devone_open,
	.release = devone_close,
	.read = devone_read,
	.write = devone_write,
	.poll = devone_poll,
};

static int devone_init(void)
{
	dev_t dev = MKDEV(devone_major, 0);
	int alloc_ret = 0;
	int major;
	int cdev_err = 0;
	struct device *class_dev = NULL;

	alloc_ret = alloc_chrdev_region(&dev, 0, devone_devs, "devone");
	if (alloc_ret)
		goto error;
	devone_major = major = MAJOR(dev);

	cdev_init(&devone_cdev, &devone_fops);
	devone_cdev.owner = THIS_MODULE;
	devone_cdev.ops = &devone_fops;
	cdev_err = cdev_add(&devone_cdev, MKDEV(devone_major, devone_minor), 1);

	if (cdev_err)
		goto error;

	/* Register class */
	devone_class = class_create(THIS_MODULE, "devone");
	if (IS_ERR(devone_class))
		goto error;
	devone_dev = MKDEV(devone_major, devone_minor);
	class_dev = device_create(devone_class, NULL, devone_dev, NULL, "devone%d", devone_minor);

	printk(KERN_ALERT "devone driver(major %d) installed.\n", major);

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

	/* Unregister class */
	device_destroy(devone_class, devone_dev);
	class_destroy(devone_class);

	cdev_del(&devone_cdev);
	unregister_chrdev_region(dev, devone_devs);

	printk(KERN_ALERT "devone driver removed.\n");
}

module_init(devone_init);
module_exit(devone_exit);
