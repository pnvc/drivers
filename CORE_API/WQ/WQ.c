#include <linux/module.h>
#include <linux/init.h>
#include <linux/workqueue.h>

static int a = 0;

static void wf(struct work_struct *w)
{
	a ++;
	pr_info("WQ: %d\n", a);
}

static struct workqueue_struct *wq;
static DECLARE_WORK(w0, wf);
static DECLARE_WORK(w1, wf);
static DECLARE_WORK(w2, wf);

static int __init WQ_init(void)
{
	wq = alloc_workqueue("WQ", WQ_UNBOUND | WQ_HIGHPRI, 0);
	if (!wq) {
		pr_err("WQ: fail alloc workqueue\n");
		return -1;
	}
	queue_work(wq, &w0);
	queue_work(wq, &w1);
	queue_work(wq, &w2);
	pr_info("WQ: inited\n");
	return 0;
}

static void __exit WQ_exit(void)
{
	destroy_workqueue(wq);
	pr_info("WQ: exited\n");
}

module_init(WQ_init);
module_exit(WQ_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("workqueue understaing by reading docs.kernel");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
