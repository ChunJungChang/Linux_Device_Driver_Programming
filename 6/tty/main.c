#include <linux/module.h>
#include <linux/init.h>
#include <linux/tty.h>
#include <linux/sched.h>

MODULE_LICENSE("DUAL BSD/GPL");

static void hook_tty_console(char *msg)
{
    struct tty_struct *tty;

    tty = current->signal->tty;

    if (tty) {
        ((tty->driver)->ops->write)(tty, msg, strlen(msg));
        ((tty->driver)->ops->write)(tty, "\r\n", 2);
    }
}

static int sample_init(void)
{
    printk("driver loaded\n");

    hook_tty_console("This message is written by sample driver");

    return 0;
}

static void sample_exit(void)
{
    printk("driver unloaded\n");
}

module_init(sample_init);
module_exit(sample_exit);
