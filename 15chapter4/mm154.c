#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>

#define MM154 "mm154"
#define MM154M "mm154: "

static int __init mm154_init(void)
{
	void *k = kmalloc(10, GFP_KERNEL);
	void *d = kmalloc(10, GFP_DMA);
	void *p = (void *)__get_free_pages(__GFP_DMA, 3);

	pr_info(MM154M "%p\n%p\n%p\n", k, d, p);
	pr_info(MM154M "%lx\n%lx\n%lx\n", __pa(k) >> PAGE_SHIFT, __pa(d) >> PAGE_SHIFT, __pa(p) >> PAGE_SHIFT);

	kfree(k);
	kfree(d);
	free_pages((unsigned long)p, 3);
	return 0;
}

static void __exit mm154_exit(void)
{
	;
}

module_init(mm154_init);
module_exit(mm154_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("DMA");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
