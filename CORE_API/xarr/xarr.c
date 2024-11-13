#include <linux/module.h>
#include <linux/init.h>
#include <linux/xarray.h>

static struct xarray xarr;

struct foo {
	int a;
	int b;
};

static struct foo f0 = {
	.a = 10,
	.b = 11,
};
static struct foo f1 = {
	.a = 30,
	.b = 31,
};
static struct foo f2 = {
	.a = 20,
	.b = 21,
};

static int __init xarr_init(void)
{
	/* create and fill xarr */
	xa_init(&xarr);
	xa_store(&xarr, 0, &f0, GFP_KERNEL);
	xa_store(&xarr, 1, &f1, GFP_KERNEL);
	xa_store(&xarr, 2, &f2, GFP_KERNEL);

	pr_info("xarr: %d\n", ((struct foo *)xa_load(&xarr, 1))->b);
	pr_info("xarr: inited\n");
	return 0;
}

static void __exit xarr_exit(void)
{
	/* destroy xarr */
	xa_destroy(&xarr);
	pr_info("xarr: exited\n");
}

module_init(xarr_init);
module_exit(xarr_exit);

MODULE_AUTHOR("pnvcc");
MODULE_DESCRIPTION("XArray example ?");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
