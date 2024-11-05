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
	wait_queue_head_t read_wait, write_wait;
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
};

#define data_add(data) 		list_add_tail(data->node, &cb.data_list)
#define data_buf(data) 		data->buf
#define data_last() 		list_last_entry(&cb.data, struct cb_data, node)
#define data_last_buf()		data_last()->buf
#define data_list_empty() 	list_empty(&cb.data_list)
#define data_del(data) 		list_del(data->node); \
					kfree(data); \
					cb.data_list_count--
#define data_end()		cb.roff == cb.woff
#define list_data(list)		list_entry(list, struct cb_data, node)

static void *data_list_by_off_div(unsigned char off)
{
	struct list_head *list = &cb.data_list;
	while (off--)
		list = list->next;
	return list_entry(list, struct cb_data, node)->buf;
}

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
	size_t count_max;
	struct list_head *head;
	void *buf;
	loff_t buf_offset;
	ssize_t retval = 0;
	size_t odd = 0;
	size_t max_read_from_page_buf = 0;
	size_t count_now = 0;

	while (data_end()) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		wait_event_interruptible(cb.read_wait, cb.roff != cb.woff);
	}

	if (mutex_lock_interruptible(&cb.mr))
		return -ERESTARTSYS;

	count_max = cb.woff < cb.roff ? RWOFF_MAX + cb.woff - cb.roff + 1
					: cb.woff - cb.roff;

	if (count > count_max)
		count = count_max;

	head = data_list_by_off_div((unsigned char)(cb.roff / PAGE_SIZE));
	buf = data_buf(list_data(head));
	buf_offset = cb.roff % PAGE_SIZE;
	buf += buf_offset;

	// it is useless

	cb.roff += retval;

	mutex_unlock(&cb.mr);

	return retval;
}

static ssize_t cb_write(struct file *filp, const char __user *ubuf,
		size_t count, loff_t *offset)
{
	if (cb.roff > cb.woff)
		wait_event_interruptible(cb.write_wait, cb.roff <= cb.woff);
	if (mutex_lock_interruptible(&cb.mr))
		return -ERESTARTSYS;
	wake_up_interruptible(&cb.read_wait);
	mutex_unlock(&cb.mw);
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
	init_waitqueue_head(&cb.write_wait);
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
