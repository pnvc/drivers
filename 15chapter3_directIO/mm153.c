#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/mm.h>
#include <linux/highmem-internal.h>


#define MM153 "mm153"
#define MM153M "mm153: "
#define nl "\n"
#define NR_DEVICES 1
#define NR_PAGES 10

static int mm153_open(struct inode *inode, struct file *filp);
static int mm153_release(struct inode *inode, struct file *filp);
static ssize_t mm153_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offset);
static ssize_t mm153_write(struct file *filp, const char __user *ubuf, size_t count, loff_t *offset);

struct mm153 {
	dev_t dev;
	struct class *class;
	struct cdev cdev;
	struct file_operations fops;
	struct device *device;
	void *buf;
	struct mutex mutex;
	wait_queue_head_t readq, writeq;
};
static struct mm153 mm153 = {
	.fops = {
		.read = mm153_read,
		.write = mm153_write,
		.open = mm153_open,
		.release = mm153_release,
	},
};
static int major = 0, minor = 0;

static int mm153_open(struct inode *inode, struct file *filp)
{
	struct mm153 *dev;

	dev = container_of(inode->i_cdev, struct mm153, cdev);
	filp->private_data = dev;

	pr_info(MM153M"mm153_open\n");

	return 0;
}

static int mm153_release(struct inode *inode, struct file *filp)
{
	pr_info(MM153M"mm153_release\n");
	return 0;
}

static ssize_t mm153_read(struct file *filp, char __user *ubuf, size_t count, loff_t *offset)
{
	struct mm153 *dev = filp->private_data;
	int retval = 0;

	if (wait_event_interruptible(dev->readq, dev->buf))
		return -ERESTARTSYS;

	if (PAGE_SIZE - *offset < count)
		count = PAGE_SIZE - *offset;

	if (!count) {
		retval = 0;
		goto end;
	}

	if (copy_to_user(ubuf, dev->buf + *offset, count)) {
		pr_info(MM153M"fail copy_to_user"nl);
		goto end;
	}

	retval = count;
	*offset += count;

	pr_info(MM153M"%s read %lu bytes"nl, current->comm, count);

end:
	return retval;
}

static ssize_t mm153_write(struct file *filp, const char __user *ubuf, size_t count, loff_t *offset)
{
	struct mm153 *dev = filp->private_data;
	size_t retval;

	if (PAGE_SIZE - *offset < count)
		count = PAGE_SIZE - *offset;

	if (!count) {
		retval = 0;
		goto end;
	}

	if (mutex_lock_interruptible(&dev->mutex))
		return -ERESTARTSYS;

	if (!dev->buf) {
		dev->buf = (void *)get_zeroed_page(GFP_KERNEL);
		if (!dev->buf) {
			pr_info(MM153M"fail get_zeroed_page"nl);
			retval = -ENOMEM;
			goto end_unlock;
		}
		pr_info(MM153M"buffed allocated"nl);
	}

	if (copy_from_user(dev->buf + *offset, ubuf, count)) {
		pr_info(MM153M"fail copy_from_user"nl);
		retval = -EFAULT;
		goto end_unlock;
	}

	struct page *pages[NR_PAGES];
	char *page_kmapped;
	long addr;
	int err = kstrtol(dev->buf + *offset, 0, &addr);
	if (err) {
		pr_info(MM153M"fail kstrtol"nl);
	} else {
		pr_info(MM153M"get user addr: 0x%lx"nl, addr);
		err = get_user_pages_fast(addr, NR_PAGES, 1, pages);
		if (err <= 0) {
			pr_info(MM153M"fail get_user_pages_fast"nl);
		} else {
			pr_info(MM153M"get_user_pages_fast %d pages"nl, err);
			page_kmapped = (char *)kmap(pages[0]);
			strcpy(page_kmapped + (addr & 0xfff), "pesos*");

			kunmap(pages[0]);

			if (!PageReserved(pages[0]))
				SetPageDirty(pages[0]);

			put_page(pages[0]);

			kunmap(pages[0]);
		}
	}

	*offset += count;

	retval = count;

	pr_info(MM153M"%s wrote %lu bytes"nl, current->comm, count);

	wake_up_interruptible(&dev->readq);

end_unlock:
	mutex_unlock(&dev->mutex);
end:
	return retval;
}

static int __init mm153_init(void)
{
	int err = 0;

	err = alloc_chrdev_region(&mm153.dev, minor, NR_DEVICES, MM153);
	if (err) {
		pr_info(MM153M"fail alloc_chrdev"nl);
		goto end;
	}

	major = MAJOR(mm153.dev);

	mm153.class = class_create(MM153);
	if (!mm153.class) {
		pr_info(MM153M"fail class_create"nl);
		goto fail_class_create;
	}

	cdev_init(&mm153.cdev, &mm153.fops);
	err = cdev_add(&mm153.cdev, mm153.dev, NR_DEVICES);
	if (err) {
		pr_info(MM153M"fail cdev_add"nl);
		goto fail_cdev_add;
	}

	mm153.device = device_create(mm153.class, NULL, mm153.dev, NULL, MM153);
	if (!mm153.device) {
		pr_info(MM153M"fail device_create"nl);
		goto fail_device_create;
	}

	mutex_init(&mm153.mutex);
	init_waitqueue_head(&mm153.readq);
	init_waitqueue_head(&mm153.writeq);

	pr_info(MM153M"init"nl);
	goto end;

fail_device_create:
fail_cdev_add:
	cdev_del(&mm153.cdev);
	class_destroy(mm153.class);

fail_class_create:
	unregister_chrdev_region(mm153.dev, NR_DEVICES);
end:
	return err;
}

static void __exit mm153_exit(void)
{
	device_destroy(mm153.class, mm153.dev);
	cdev_del(&mm153.cdev);
	class_destroy(mm153.class);
	unregister_chrdev_region(mm153.dev, NR_DEVICES);
	if (mm153.buf)
		free_page((unsigned long)mm153.buf);
	pr_info(MM153"exit"nl);;
}

module_init(mm153_init);
module_exit(mm153_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("direct IO");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
