#include <linux/module.h>
#include <linux/init.h>
#include <linux/mm.h>
#include <linux/vmalloc.h>

#define MM151 "mm151"
#define MM151M "mm151: "

#define PAGE_SIZE_MUL_L 10
#define PAGE_SIZE_MUL 10

static int __init mm151_init(void)
{
	void *addr = kmalloc(PAGE_SIZE * PAGE_SIZE_MUL_L, GFP_KERNEL);
	if (!addr)
		return -ENOMEM;

	struct page *pg = virt_to_page(addr);
	if (!pg)
		pr_info(MM151M "no page!\n");

	void *pg_addr;
	pg_addr = page_address(pg);
	if (!pg_addr)
		pr_info(MM151M "no page_address\n");
	int pfn = (__pa(addr) >> PAGE_SHIFT);
	pr_info(MM151M "%i pfn\n", pfn);
	pr_info(MM151M "%lu pfn from page addr\n", page_to_pfn(pg));
	pr_info(MM151M "%p addr\n", addr);
	pr_info(MM151M "%p page addr\n", pg_addr);
	pr_info(MM151M "%p page ptr\n", pg);
	pr_info(MM151M "%p page ptr from pfn\n", pfn_to_page(pfn));
	pr_info(MM151M "%lX physical addr\n", __pa(addr));
	pr_info(MM151M "%lX physical addr of page\n", __pa(pg_addr));
	pr_info(MM151M "%lu page size\n", PAGE_SIZE);
	pr_info(MM151M "%i page shift\n", PAGE_SHIFT);
	for (int i = 0; i < PAGE_SIZE * PAGE_SIZE_MUL_L; i++) {
		//pr_info(MM151M "%lX phys addr+%i\n", __pa(addr + i), i);
		if (i > 0 && __pa(addr + i) - __pa(addr + i - 1) != 1) {
			pr_info(MM151M "addr separated!\n");
			i = PAGE_SIZE * PAGE_SIZE_MUL_L;
		}
	}
	kfree(addr);

	void *vaddr = vmalloc(PAGE_SIZE * PAGE_SIZE_MUL);
	if (!vaddr) {
		pr_info(MM151M"unable vmalloc\n");
		return -ENOMEM;
	}
	pr_info(MM151M "%p vaddr\n", vaddr);
	int pnfv = __pa(vaddr) >> PAGE_SHIFT;
	struct page *pgv = pfn_to_page(pnfv);
	if (!pgv)
		pr_info(MM151M "no page virtual address\n");
	for (int i = 0; i < PAGE_SIZE * PAGE_SIZE_MUL; i++) {
		//pr_info(MM151M "%lX phys vaddr+%i\n", __pa(vaddr + i), i);
		if (i > 0 && __pa(vaddr + i) - __pa(vaddr + i - 1) != 1) {
			pr_info(MM151M "vaddr separated!\n");
			i = PAGE_SIZE * PAGE_SIZE_MUL;
		}
	}
	vfree(vaddr);

	return 0;
}

static void __exit mm151_exit(void)
{
	;
}

module_init(mm151_init);
module_exit(mm151_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("mem manag 15.1");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
