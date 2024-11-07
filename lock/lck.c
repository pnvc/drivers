#include <linux/module.h>
#include <linux/init.h>
#include <linux/spinlock.h>

static DEFINE_SPINLOCK(lck);

static void foo(void)
{
	spin_lock(&lck);
}

static int __init lck_init(void)
{
	unsigned long flags;
	foo();
	pr_info("lck: inited\n");
	return 0;
}

static void __exit lck_exit(void)
{
	pr_info("lck: exited\n");
}

module_init(lck_init);
module_exit(lck_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("lock test kek");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
