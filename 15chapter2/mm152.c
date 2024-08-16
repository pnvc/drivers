#include <linux/module.h>
#include <linux/init.h>
#include <linux/cdev.h>
#include <linux/fs.h>


#define MM152 "mm152"
#define MM152M "mm152: "
#define NR_DEVICES 1
#define F_L ". %s %u\n"

/* decl */
struct mm152 {
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
/* decl */

/* defi */
static struct mm152 mm152 = {
	.dev = 0,
	.fops = {
		.mmap = mm152_mmap
	}
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

static int mm152_mmap(struct file *filp, struct vm_area_struct *vma)
{
	return 0;
}
/* defi */

/* init */
/* init */

static int __init mm152_init(void)
{
	int err;

	pr_info(MM152M "1\n");
	err = dev_reg(&mm152);
		return err;


	pr_info(MM152M "2\n");
	err = mm152_class_create(&mm152);
	if (err) {
		unregister_chrdev_region(mm152.dev, NR_DEVICES);
		return err;
	}

	pr_info(MM152M "3\n");
	err = mm152_device_create(&mm152);
	if (err) {
		class_destroy(mm152.class);
		unregister_chrdev_region(mm152.dev, NR_DEVICES);
		return err;
	}

	pr_info(MM152M "4\n");
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
