#include <linux/init.h>
#include <linux/module.h>
#include <linux/err.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/completion.h>
#include <linux/delay.h>
#include <asm/current.h>
#include <asm/unistd.h>

MODULE_LICENSE("Dual BSD/GPL");

static struct completion comp;
static struct task_struct *thr_task;

static int sample_thread(void *num)
{
    unsigned int timeout;

    printk("%s called\n", __func__);

    for (;;) {
        if (kthread_should_stop()) break;
        do {
            set_current_state(TASK_INTERRUPTIBLE);
            timeout = schedule_timeout(3 * HZ);
        } while(timeout);
    }

    printk("%s leaved\n", __func__);
    complete_and_exit(&comp, 0); /* return here */

    return 0;
}

static int sample_init(void)
{
    int err;

	printk("sample driver installed.\n");

    init_completion(&comp);

    /*
     * Use "ps aux | grep sample_thr" or "ps -ef | grep sample_thr"
     * to check the thread is running.
     */
    thr_task = kthread_create(sample_thread, NULL, "sample_thr");
    if (IS_ERR(thr_task)) {  
        printk(KERN_ALERT "Thread Creation Failed.\n");  
        err = PTR_ERR(thr_task);  
        thr_task = NULL;  
        return err;  
    }  
    printk("Thread Created Sucessfully.\n");
    wake_up_process(thr_task);

	return 0;
}

static void sample_exit(void)
{
    int ret;

    if (thr_task) {
        ret = kthread_stop(thr_task);
        thr_task = NULL;
    }
    if (!ret) {
        printk("Thread stopped.\n");
    }

    wait_for_completion(&comp);
	printk("sample driver removed.\n");
}

module_init(sample_init);
module_exit(sample_exit);
