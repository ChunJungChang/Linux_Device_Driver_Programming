#include <linux/module.h>
#include <linux/init.h>
#include <linux/sched.h>

MODULE_LICENSE("Dual BSD/GPL");

#define SLEEP_TIMEOUT (6*HZ)
#define WAKEUP_TIMEOUT (5*HZ)

static struct timer_list tickfn;
static wait_queue_head_t wait;
static int condition = 0;

static void sample_timeout(unsigned long arg)
{
    wait_queue_head_t *wq = (wait_queue_head_t *)arg;

    printk("wq %p (%s)\n", wq, __func__);
    /* If you want to timeout ocurred, comment out next two line */
    condition = 1;
    wake_up(wq);
}

static int sample_init(void)
{
    long val;

    printk("driver loaded: %p\n", &tickfn);

    init_waitqueue_head(&wait);

    init_timer(&tickfn);
    /* Call the function when expire */
    tickfn.function = sample_timeout;
    tickfn.data = (unsigned long)&wait;
    tickfn.expires = jiffies + WAKEUP_TIMEOUT;
    add_timer(&tickfn);

    condition = 0;
    val = wait_event_timeout(wait, condition, SLEEP_TIMEOUT);
    printk("val: %ld (%s)\n", val, __func__);
    if (val == 0) { /* timeout */
        printk("Timeout ocurred. (%s)\n", __func__);
    }

    return 0;
}

static void sample_exit(void)
{
    del_timer_sync(&tickfn);

    printk("driver loaded\n");
}

module_init(sample_init);
module_exit(sample_exit);
