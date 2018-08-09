#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>
#include <linux/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

#define PROCNAME "driver/sample"

static int sample_flag = 0;
int len, temp;

static ssize_t sample_proc_read(
    struct file *fp,
    char *buf, /* the destination buffer */
    size_t buf_size, /* size of buffer */
    loff_t *offset) /* offset in destination buffer */
{
    static int finished = 0;
    int len = 0;

    printk(KERN_INFO "%s called\n", __func__);

    if (finished) {
        printk(KERN_INFO "procfs_read: END\n");
        finished = 0;
        return 0;
    }

    finished = 1;
    //len = sprintf(buf, "I wanna see the movie\n");
    len = sprintf(buf, "%d\n", sample_flag);
 
    return len;
}

static ssize_t sample_proc_write(
    struct file *fp,
    const char *buf, /* the destination buffer */
    size_t buf_size, /* size of buffer */
    loff_t *offset) /* offset in destination buffer */
{
    char buf_tmp[16];
    unsigned long len = buf_size;
    int n;

    printk(KERN_INFO "%d (%s)\n", (int)len, __func__);

    if (len >= sizeof(buf_tmp))
        len = sizeof(buf_tmp) - 1;

    if (copy_from_user(buf_tmp, buf, len))
        return -EFAULT;
    buf_tmp[len] = '\0';

    n = simple_strtol(buf_tmp, NULL, 10);
    if (n == 0)
        sample_flag = 0;
    else
        sample_flag = 1;

    return len;
} 

struct file_operations sample_proc_fops = {
    .owner = THIS_MODULE,
    .read = sample_proc_read,
    .write = sample_proc_write,
};

static int sample_init(void)
{
    struct proc_dir_entry *entry = NULL;

    /* add /proc */
    entry = proc_create(PROCNAME, 0666, NULL, &sample_proc_fops);
    if (entry == NULL) {
        printk(KERN_WARNING "sample: unable to create /proc entry\n");
        return -ENOMEM;
    }

    printk("driver loaded\n");

    return 0;
}

static void sample_exit(void)
{
    remove_proc_entry(PROCNAME, NULL);

    printk(KERN_ALERT "driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);
