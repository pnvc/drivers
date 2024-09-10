#include <linux/module.h>
#include <linux/init.h>
#include <linux/vmalloc.h>

#define MM154 "mm154"
#define MM154M "mm154: "

static int __init mm154_init(void)
{
	void *v = vmalloc(PAGE_SIZE * 2);
	void *k = kmalloc(PAGE_SIZE * 2, GFP_KERNEL);
	void *d = kmalloc(PAGE_SIZE * 2, GFP_DMA);
	unsigned long p = __get_free_pages(GFP_DMA, 2);

	pr_info(MM154M"vir:\n"MM154M"v %px\n"MM154M"k %px\n"MM154M"d %px\n"MM154M"p %lx\n", v, k, d, p);
	pr_info(MM154M"phy:\n"MM154M"v %lx\n"MM154M"k %lx\n"MM154M"d %lx\n"MM154M"p %lx\n", __pa(v), __pa(k), __pa(d), __pa(p));
	pr_info(MM154M"pfn:\n"MM154M"v %lx\n"MM154M"v %lx\n"MM154M"v %lx\n"MM154M"v %lx\n",
			__pa(v) >> PAGE_SHIFT,
			__pa(k) >> PAGE_SHIFT,
			__pa(d) >> PAGE_SHIFT,
			__pa(p) >> PAGE_SHIFT);

/*
	vfree(v);
	kfree(k);
	kfree(d);
	free_pages((unsigned long)p, 2);
*/

	return 0;
}

static void __exit mm154_exit(void)
{
}

module_init(mm154_init);
module_exit(mm154_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("DMA");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
