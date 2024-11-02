#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/circ_buf.h>
#include <linux/mutex.h>

struct cb_data {
	char buf[PAGE_SIZE];
	struct list_head node;
};

#define RWOFF_MAX		((PAGE_SIZE << 2) - 1)

struct cb {
	struct list_head data_list;
	char data_list_count;
	dev_t dev;
	struct cdev cdev;
	struct mutex mr, mw;
	loff_t roff, woff;
	wait_queue_head_t read_wait;
	bool allow_read;
};

static int cb_open(struct inode *inode, struct file *filp);
static int cb_release(struct inode *inode, struct file *filp);
static ssize_t cb_read(struct file *filp, char __user *ubuf, size_t count,
		loff_t *offset);
static ssize_t cb_write(struct file *filp, const char __user *ubuf,
		size_t count, loff_t *offset);

static struct file_operations cb_fops = {
	.open = cb_open,
	.release = cb_release,
	.read = cb_read,
	.write = cb_write
};

static struct cb cb = {
	.roff =			0,
	.woff =			0,
	.dev =			0,
	.data_list_count =	0,
	.allow_read = 		false,
};
#define data_add(data) 		list_add_tail(data->node, &cb.data_list)
#define data_buf(data) 		data->data
#define data_last() 		list_last_entry(&cb.data, struct cb, node)
#define data_last_buf()		data_last()->buf
#define data_list_empty() 	list_empty(&cb.data_list)
#define data_del(data) 		list_del(data->node); \
					kfree(data); \
					cb.data_list_count--
#define data_end()		cb.roff == cb.woff

static int cb_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static int cb_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t cb_read(struct file *filp, char __user *ubuf, size_t count,
		loff_t *offset)
{
	int ret;

	if (data_end())
		if (wait_event_interruptible(cb.read_wait, cb.roff != cb.woff))
			return -ERESTARTSYS;

	return count;
}

static ssize_t cb_write(struct file *filp, const char __user *ubuf,
		size_t count, loff_t *offset)
{
	wake_up_interruptible(&cb.read_wait);
	return count;
}

static int __init cb_init(void)
{
	int err;

	err = alloc_chrdev_region(&cb.dev, 0, 1, "cb");
	if (err) {
		pr_err("cb: fail alloc chrdev: %d\n", err);
		return err;
	}
	pr_info("cb: major %d, minor %d\n", MAJOR(cb.dev), MINOR(cb.dev));


	cdev_init(&cb.cdev, &cb_fops);
	cb.cdev.owner = THIS_MODULE;
	err = cdev_add(&cb.cdev, cb.dev, 1);
	if (err) {
		pr_err("cb: fail cdev add: %d\n", err);
		unregister_chrdev_region(cb.dev, 1);
		return err;
	}

	INIT_LIST_HEAD(&cb.data_list);
	init_waitqueue_head(&cb.read_wait);
	mutex_init(&cb.mw);

	pr_info("cb: inited\n");
	return 0;
}

static void __exit cb_exit(void)
{
	cdev_del(&cb.cdev);
	unregister_chrdev_region(cb.dev, 1);
	pr_info("cb: exited\n");
}

module_init(cb_init);
module_exit(cb_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("circular buffer example");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
