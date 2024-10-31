#include <linux/module.h>
#include <linux/init.h>

struct mys {
	int a;
};

static void free_mys(struct mys *obj)
{
	kfree(obj);
}

DEFINE_FREE(free_mys, struct mys *, if (_T) free_mys(_T))
static int __init df_init(void)
{
	struct mys *m __free(free_mys) = NULL;
	m = kmalloc(sizeof(*m), GFP_KERNEL);
	if (!m)
		return -ENOMEM;

	pr_info("df: inited\n");
	return 0;
}

static void __exit df_exit(void)
{
	pr_info("df: exited\n");
}

module_init(df_init);
module_exit(df_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("define free examine");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
