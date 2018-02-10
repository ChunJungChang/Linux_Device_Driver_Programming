#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/uaccess.h>

MODULE_LICENSE("Dual BSD/GPL");

#define PROCNAME "driver/sample"
#define DUMMY_BUFSIZE 131075
static char dummy[DUMMY_BUFSIZE];
int counter = 0; /* number of entries to be transferred */
int temp = DUMMY_BUFSIZE;

/*
static int sample_proc_read(char *page, char **start, off_t off,
    int count, int *eof, void *data)
{
    int len = 0;

    printk("page=%p start=%p off=%d count=%d *eof=%d data=%p\n",
        page, *start, (int)off, count, *eof, data);

    len = DUMMY_BUFSIZE;
    if (len > PAGE_SIZE)
        return -ENOBUFS;

    memcpy(page, dummy, len);
    *eof = 1;

    printk("len=%d (%s)\n", len, __func__);

    return len;
}
*/

static int sample_proc_read(
    struct file *fp,
    char *buf, /* the destination buffer */
    size_t buf_size, /* size of buffer */
    loff_t *offset) /* offset in destination buffer */
{
    char *data;

    printk("counter=%d fp=%p buf=%p buf_size=%zu *offset=%lld\n",
            counter, fp, buf, buf_size, *offset);
    printk("counter=%d buf_size=%zu temp=%d\n",
            counter, buf_size, temp);

    data = PDE_DATA(file_inode(fp));
    if (!(data)) {
        printk(KERN_INFO "no data\n");
        return 0;
    }

    if (buf_size > temp) {
        buf_size = temp;
    }
    temp -= buf_size; /* Read End when buf_size == 0 */
    copy_to_user(buf, data, buf_size);
    if (buf_size == 0)
        temp = DUMMY_BUFSIZE;
    printk("counter=%d buf_size=%zu temp=%d\n",
            counter, buf_size, temp);
    counter++;

    return buf_size;
}

struct file_operations sample_proc_fops = {
    .owner = THIS_MODULE,
    .read = sample_proc_read,
};

static int sample_init(void)
{
    struct proc_dir_entry *entry;
    int i;

    /* add /proc */
    entry = proc_create_data(PROCNAME, S_IRUGO | S_IWUGO, NULL,
        &sample_proc_fops, dummy);
    if (entry == NULL) {
        printk(KERN_WARNING "sample: unable to create /proc entry\n");
    }

    for (i = 0;i < DUMMY_BUFSIZE;i++) {
        dummy[i] = 'A' + (i % 26);
    }

    printk("driver loaded\n");

    return 0;
}

static void sample_exit(void)
{
    remove_proc_entry(PROCNAME, NULL);

    printk("driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);
