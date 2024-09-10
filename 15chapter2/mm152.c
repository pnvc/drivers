#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/mm.h>


#define MM152 "mm152"
#define MM152M "mm152: "
#define NR_DEVICES 1
#define F_L ". %s %u\n"

struct mm152 {
	void *buf;
	int major, minor;
	dev_t dev;
	struct cdev cdev;
	struct file_operations fops;
	struct class *class;
};

static int dev_reg(struct mm152 *); /* reg dev_t */
static int cdev_reg(struct mm152 *); /* reg struct cdev */
static int mm152_class_create(struct mm152 *); /* create mm152 class */
static int mm152_device_create(struct mm152 *); /* create mm152 device */
static int mm152_mmap(struct file *, struct vm_area_struct *); // mmap for device
static int mm152_mremap(struct vm_area_struct *); // mremap for device
static int mm152_may_split(struct vm_area_struct *, unsigned long); // before mremap ?
static vm_fault_t mm152_fault(struct vm_fault *); // fault after mmap?
static int mm152_mprotect(struct vm_area_struct *, unsigned long, unsigned long, unsigned long);
static void mm152_mmap_open(struct vm_area_struct *);
static void mm152_mmap_close(struct vm_area_struct *);
static int mm152_open(struct inode *, struct file *); // open mm152 dev
// read mm152
static ssize_t mm152_read(struct file *, char __user *, size_t, loff_t *);
// write mm152
static ssize_t mm152_write(struct file *, const char __user *, size_t, loff_t *);

static struct mm152 mm152 = {
	.dev = 0,
	.fops = {
		.mmap = mm152_mmap,
		.open = mm152_open,
		.read = mm152_read,
		.write = mm152_write,
	}
};

static struct vm_operations_struct mm152_vma_ops = {
	.open = mm152_mmap_open,
	.close = mm152_mmap_close,
	.mremap = mm152_mremap,
	.may_split = mm152_may_split,
	.fault = mm152_fault,
	.mprotect = mm152_mprotect,
};

static int dev_reg(struct mm152 *mm152)
{
	int err;

	if (mm152->dev)
		return 0;

	err = alloc_chrdev_region(&mm152->dev, mm152->minor, NR_DEVICES, MM152);
	if (err) {
		pr_info(MM152M "alloc_chrdev_region failed" F_L, __FILE__, __LINE__);
		return err;
	}

	mm152->major = MAJOR(mm152->dev);
	mm152->minor = MINOR(mm152->dev);
	pr_info(MM152 "%d %d\n", mm152->major, mm152->minor);

	return 0;
}

static int cdev_reg(struct mm152 *mm152)
{
	int err;

	cdev_init(&mm152->cdev, &mm152->fops);
	mm152->cdev.owner = THIS_MODULE;
	err = cdev_add(&mm152->cdev, mm152->dev, NR_DEVICES);
	if (err) {
		pr_info(MM152M "cdev_add failed" F_L, __FILE__, __LINE__);
		cdev_del(&mm152->cdev);
		return err;
	}

	return 0;
}

static int mm152_class_create(struct mm152 *mm152)
{
	mm152->class = class_create(MM152);
	if (!mm152->class) {
		pr_info(MM152M "class_create failed" F_L, __FILE__, __LINE__);
		return -ENOMEM;
	}

	return 0;
}

static int mm152_device_create(struct mm152 *mm152)
{
	if (!device_create(mm152->class, NULL, mm152->dev, NULL, MM152)) {
		pr_info(MM152M "device_create filed" F_L, __FILE__, __LINE__);
		return -ENOMEM;
	}

	return 0;
}

static int mm152_open(struct inode *i, struct file *f)
{
	struct mm152 *mm152;

	mm152 = container_of(i->i_cdev, struct mm152, cdev);
	f->private_data = mm152;

	return 0;
}

static ssize_t mm152_read(struct file *filp, char __user *ubuf, 
		size_t count, loff_t *offset)
{
	struct mm152 *m = filp->private_data;
	copy_to_user(ubuf, m->buf, count);
	return count;
}

static ssize_t mm152_write(struct file *filp, const char __user *ubuf,
		size_t count, loff_t *offset)
{
	struct mm152 *m = filp->private_data;
	copy_from_user(m->buf, ubuf, count);
	return count;
}

static int mm152_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct mm152 *m = filp->private_data;
	//m->buf = page_to_virt(pfn_to_page(vma->vm_pgoff));
	//vma->vm_pgoff = __pa(m->buf) >> PAGE_SHIFT;
/*
	if (remap_pfn_range(vma, vma->vm_start, vma->vm_pgoff,
				vma->vm_end - vma->vm_start,
				vma->vm_page_prot))
		return -EAGAIN;
*/
	vma->vm_ops = &mm152_vma_ops;
	mm152_mmap_open(vma);
	return 0;
}

static int mm152_may_split(struct vm_area_struct *area, unsigned long addr)
{
	pr_info(MM152M "may_split called\n");
	return 0;
}

static vm_fault_t mm152_fault(struct vm_fault *)
{
	pr_info(MM152M "fault called\n");
	return 0;
}

static int mm152_mprotect(struct vm_area_struct *vma, unsigned long start, unsigned long end, unsigned long nflags)
{
	pr_info(MM152M "mprotect\n");
	return 0;
}

static int mm152_mremap(struct vm_area_struct *vma)
{
	pr_info(MM152M "mremap called\n");
	return 0;
}

static void mm152_mmap_open(struct vm_area_struct *vma)
{
	pr_info(MM152M"vma open\n"
MM152M"%lx vm_start\n"
MM152M"%px vm_start to page\n"
MM152M"%px page virt addr\n"
MM152M"%lx page virt addr to phys\n"
MM152M"%lx vm_start to phys\n"
MM152M"%lx page to pfn\n"
MM152M"%px pfn to page\n"
MM152M"%lx vm_pgoff\n"
MM152M"%lx vm_pgoff << PAGE_SHIT\n"
MM152M"%px vm_pgoff to page\n"
MM152M"%px kern page to page addr\n"
MM152M"%px kern page to virt\n",
		vma->vm_start,
		virt_to_page(vma->vm_start),
		page_address(virt_to_page(vma->vm_start)),
		__pa(page_address(virt_to_page(vma->vm_start))),
		__pa(vma->vm_start),
		page_to_pfn(virt_to_page(vma->vm_start)),
		pfn_to_page(page_to_pfn(virt_to_page(vma->vm_start))),
		vma->vm_pgoff,
		vma->vm_pgoff << PAGE_SHIFT,
		pfn_to_page(vma->vm_pgoff),
		page_address(pfn_to_page(vma->vm_pgoff)),
		page_to_virt(pfn_to_page(vma->vm_pgoff)));
}
static void mm152_mmap_close(struct vm_area_struct *vma)
{
	pr_info(MM152M"vma close\n");
}

static int __init mm152_init(void)
{
	int err;
	
	mm152.buf = kmalloc(PAGE_SIZE * 5, GFP_KERNEL);
	if (!mm152.buf) {
		pr_info(MM152M"failed kmalloc"F_L, __FILE__, __LINE__);
		return -ENOMEM;
	}
	pr_info(MM152M"mm152 virt buf: %px\n", mm152.buf);

	err = dev_reg(&mm152);
	if (err)
		return err;


	err = mm152_class_create(&mm152);
	if (err) {
		unregister_chrdev_region(mm152.dev, NR_DEVICES);
		return err;
	}

	err = mm152_device_create(&mm152);
	if (err) {
		class_destroy(mm152.class);
		unregister_chrdev_region(mm152.dev, NR_DEVICES);
		return err;
	}

	err = cdev_reg(&mm152);
	if (err) {
		device_destroy(mm152.class, mm152.dev);
		class_destroy(mm152.class);
		unregister_chrdev_region(mm152.dev, NR_DEVICES);
		return err;
	}

	pr_info(MM152M "start\n");
	return 0;
}

static void __exit mm152_exit(void)
{
	if (mm152.buf)
		kfree(mm152.buf);
	device_destroy(mm152.class, mm152.dev);
	class_destroy(mm152.class);
	cdev_del(&mm152.cdev);
	unregister_chrdev_region(mm152.dev, NR_DEVICES);
	pr_info(MM152M "exit\n");
}

module_init(mm152_init);
module_exit(mm152_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("mmap implement");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
