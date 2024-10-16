#include <linux/module.h>
#include <linux/init.h>
#include <linux/vmalloc.h>
#include <linux/cdev.h>
#include <linux/fs.h>

#define MM154 "mm154"
#define MM154M "mm154: "
#define nl "\n"

struct mm154 {
	struct file_operations fops;
	struct cdev cdev;
	struct class *class;
	struct device *device;
	void *buf;
	int major;
	int minor;
	dev_t dev;
};

static int mm154_open(struct inode *inode, struct file *filp);
static int mm154_release(struct inode *inode, struct file *filp);
static ssize_t mm154_write(struct file *filp, const char __user *ubuf,
		size_t count, loff_t *offset);
static ssize_t mm154_read(struct file *filp, char __user *ubuf,
		size_t count, loff_t *offset);

static struct mm154 mm154 = {
	.major = 0,
	.minor = 0,
	.fops = {
		.open = mm154_open,
		.release = mm154_release,
		.write = mm154_write,
		.read = mm154_read
	}
};

static int mm154_open(struct inode *inode, struct file *filp)
{
	struct mm154 *filp_priv_data = container_of(inode->i_cdev, struct mm154, cdev);
	filp->private_data = filp_priv_data;
	return 0;
}

static int mm154_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t mm154_write(struct file *filp, const char __user *ubuf,
		size_t count, loff_t *offset)
{
	return 1;
}

static ssize_t mm154_read(struct file *filp, char __user *ubuf,
		size_t count, loff_t *offset)
{
	return 0;
}

static inline void msg(const char *m) { pr_info(MM154M"%s"nl, m); }

// INIT AND EXIT
static int __init mm154_init(void)
{
	int retval = 0;

	mm154.buf = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!mm154.buf) {
		pr_info(MM154M"failed kmalloc mm154.buf, %s:%d"nl,
				__FILE__, __LINE__);
		retval = -ENOMEM;
		goto error;
	}

	retval = alloc_chrdev_region(&mm154.dev, mm154.minor, 1, MM154);
	if (retval) {
		pr_info(MM154M"failed alloc chrdev region, %s:%d, errno: %d"nl,
				__FILE__, __LINE__, retval);
		goto error;
	}

	mm154.class = class_create(MM154);
	if (IS_ERR(mm154.class)) {
		pr_info(MM154M"failed class create, %s:%d, errno: %ld"nl,
				__FILE__, __LINE__, PTR_ERR(mm154.buf));
		retval = PTR_ERR(mm154.class);
		goto error;
	}

	cdev_init(&mm154.cdev, &mm154.fops);
	retval = cdev_add(&mm154.cdev, mm154.dev, 1);
	if (retval) {
		pr_info(MM154M"failed cdev add, %s:%d, errno: %d"nl,
				__FILE__, __LINE__, retval);
		goto error;
	}

	mm154.device = device_create(mm154.class, NULL, mm154.dev, NULL, MM154);
	if (IS_ERR(mm154.device)) {
		pr_info(MM154M"failed device create, %s:%d, error: %ld"nl,
				__FILE__, __LINE__, PTR_ERR(mm154.device));
		retval = PTR_ERR(mm154.device);
		goto error;
	}

	msg("started je");
	return retval;

error:
	kfree(mm154.buf);
	unregister_chrdev_region(mm154.dev, 1);
	cdev_del(&mm154.cdev);
	class_destroy(mm154.class);
	return retval;
}

static void __exit mm154_exit(void)
{
	kfree(mm154.buf);
	cdev_del(&mm154.cdev);
	unregister_chrdev_region(mm154.dev, 1);
	device_destroy(mm154.class, mm154.dev);
	class_destroy(mm154.class);
	msg("exited");
}

module_init(mm154_init);
module_exit(mm154_exit);

MODULE_AUTHOR("nclud");
MODULE_DESCRIPTION("DMA");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
