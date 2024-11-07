#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kdev_t.h>
#include <linux/cdev.h>
#include <linux/circ_buf.h>
#include <linux/mutex.h>
#include <linux/delay.h>
#include <linux/interrupt.h>

struct cb_data {
	char buf[PAGE_SIZE];
	struct list_head node;
};

#define CB_DATA_SIZE		(PAGE_SIZE << 2)

struct cb {
	struct list_head data_list;
	char data_list_count;
	dev_t dev;
	struct cdev cdev;
	struct mutex mr, mw;
	unsigned short roff, woff;
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

#define data_add(data) 		list_add_tail(&data->node, &cb.data_list)
#define data_buf(data) 		data->buf
#define data_last() 		list_last_entry(&cb.data, struct cb_data, node)
#define data_last_buf()		data_last()->buf
#define data_list_empty() 	list_empty(&cb.data_list)
#define data_del(data) 		list_del(data->node); \
					kfree(data); \
					cb.data_list_count--
#define data_end()		cb.roff == cb.woff
#define list_data(list)		list_entry(list, struct cb_data, node)

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
	size_t count_max, count_now;
	ssize_t retval = 0;
	unsigned char buf_num;
	unsigned short buf_offset;
	struct list_head *list = &cb.data_list;
	struct cb_data *data;
	void *buf;
	size_t max_first_count;

	count_max = CIRC_CNT(cb.woff, cb.roff, CB_DATA_SIZE);
	while (!count_max) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		pr_info("cb: read sleep\n");
		if (wait_event_interruptible(cb.read_wait, (count_max = 
						CIRC_CNT(cb.woff, cb.roff,
							CB_DATA_SIZE))))
			return -ERESTARTSYS;
		pr_info("cb: read woke up\n");
	}

	if (mutex_lock_interruptible(&cb.mr))
		return -ERESTARTSYS;

	if (count > count_max)
		count = count_max;

	list = list->next;

	buf_offset = cb.roff % PAGE_SIZE;
	buf_num = cb.roff / PAGE_SIZE;

	while (buf_num--)
		list = list->next;

	max_first_count = PAGE_SIZE - buf_offset;
	count_now = count > max_first_count ? max_first_count : count;
	data = list_data(list);
	buf = data_buf(data);
	buf += buf_offset;

	if (copy_to_user(ubuf, buf, count_now)) {
		mutex_unlock(&cb.mr);
		return -EFAULT;
	}

	retval += count_now;
	count -= count_now;

	while (count) {
		count_now = count / PAGE_SIZE ? PAGE_SIZE : count;
		list = list->next;
		data = list_data(list);
		buf = data_buf(data);
		if (copy_to_user(ubuf, buf, count_now))
			goto end; /* anyway we have some retval */
		retval += count_now;
		count -= count_now;
	}

end:
	cb.roff += retval;
	if (cb.roff >= CB_DATA_SIZE)
		cb.roff = cb.roff - CB_DATA_SIZE;
	pr_info("cb: %d %d\n", cb.woff, cb.roff);
	wake_up_interruptible(&cb.write_wait);
	mutex_unlock(&cb.mr);
	return retval;
}

static ssize_t cb_write(struct file *filp, const char __user *ubuf,
		size_t count, loff_t *offset)
{
	size_t buf_space;
	struct list_head *list = &cb.data_list;
	struct cb_data *data;
	void *buf;
	ssize_t retval = 0;
	unsigned short buf_offset;
	unsigned char buf_num;
	size_t max_first_count;
	size_t count_now;

	buf_space = CIRC_SPACE(cb.woff, cb.roff, CB_DATA_SIZE);
	while (!buf_space) {
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		if (wait_event_interruptible(cb.write_wait, (buf_space =
						CIRC_SPACE(cb.woff, cb.roff,
							CB_DATA_SIZE))))
			return -ERESTARTSYS;
	}

	if (mutex_lock_interruptible(&cb.mw))
		return -ERESTARTSYS;

	if (count > buf_space)
		count = buf_space;

	if (list_empty(list)) {
		while (count) {
			count_now = count > PAGE_SIZE ? PAGE_SIZE : count;
			count -= count_now;
			data = kzalloc(sizeof(*data), GFP_KERNEL);
			if (!data) {
				if (retval)
					goto end;
				mutex_unlock(&cb.mw);
				return -ENOMEM;
			}
			data_add(data);
			buf = data_buf(data);
			if (copy_from_user(buf, ubuf, count_now)) {
				if (retval)
					goto end;
				mutex_unlock(&cb.mw);
				return -EFAULT;
			}
			retval += count_now;
		}
		goto end;
	}

	list = list->next;

	buf_offset = cb.woff % PAGE_SIZE;
	buf_num = cb.woff / PAGE_SIZE;

	while (buf_num--)
		list = list->next;

	max_first_count = PAGE_SIZE - buf_offset;
	count_now = count > max_first_count ? max_first_count : count;
	data = list_data(list);
	buf = data_buf(data);
	buf += buf_offset;
	buf = 0;

	if (copy_from_user(buf, ubuf, count_now)) {
		mutex_unlock(&cb.mw);
		return -EFAULT;
	}

	retval += count_now;
	count -= count_now;

	while (count) {
		count_now = count > PAGE_SIZE ? PAGE_SIZE : count;
		
		list = list->next;
		if (list == &cb.data_list) {
			data = kzalloc(sizeof(*data), GFP_KERNEL);
			if (!data)
				goto end;
			list_add_tail(&data->node, list);
		} else
			data = list_data(list);
		buf = data_buf(data);
		if (copy_from_user(buf, ubuf, count_now))
			goto end; /* anyway we have some retval */
		retval += count_now;
		count -= count_now;
	}

end:
	cb.woff += retval;
	if (cb.woff >= CB_DATA_SIZE)
		cb.woff = cb.woff - CB_DATA_SIZE;
	pr_info("cb: %d %d\n", cb.woff, cb.roff);
	wake_up_interruptible(&cb.read_wait);
	mutex_unlock(&cb.mw);
	return retval;
}

static DEFINE_SPINLOCK(lck);

static int __init cb_init(void)
{
	int err;

	unsigned long flag;
	/*
	disable_irq_nosync(20);
	disable_irq_nosync(12);
	*/
	disable_irq_nosync(1);
	disable_irq_nosync(18);
	spin_lock_irqsave(&lck, flag);
	mdelay(10000);
	spin_unlock_irqrestore(&lck, flag);
	enable_irq(18);
	enable_irq(1);
	/*
	enable_irq(12);
	enable_irq(20);
	*/

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
	mutex_init(&cb.mr);

	pr_info("cb: inited\n");
	return 0;
}

static void __exit cb_exit(void)
{
	struct list_head *cur, *next;
	struct cb_data *data;
	cdev_del(&cb.cdev);
	unregister_chrdev_region(cb.dev, 1);

	list_for_each_safe(cur, next, &cb.data_list) {
		data = list_entry(cur, struct cb_data, node);
		list_del(cur);
		kfree(data);
	}

	pr_info("cb: exited\n");
}

module_init(cb_init);
module_exit(cb_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("circular buffer example");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
