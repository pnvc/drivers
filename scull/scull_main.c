#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/semaphore.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include "scull_main.h"

static int scull_major = 0;
static int scull_minor = 0;
static int scull_nr_devs = 4;
static int scull_quantum = 40000;
static int scull_qset = 10000;
static char *scull_name = "scull";
module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(scull_nr_devs, int, S_IRUGO);
module_param(scull_quantum, int, S_IRUGO);
module_param(scull_qset, int, S_IRUGO);

/* -------------------------------- */
static struct scull_dev d = {
	.size = 0,
	.quantum = 40000,
	.qset = 10000,
	.data = NULL,
};

static struct file_operations scull_fops = {
	.owner = THIS_MODULE,
	.llseek = scull_llseek,
	.read = scull_read,
	.write = scull_write,
/*	.ioctl = scull_ioctl,*/
	.open = scull_open,
	.release = scull_release,
};

static int reg_dev(void)
{
	int result;

	if (scull_major) {
		d.dev = MKDEV(scull_major, scull_minor);
		result = register_chrdev_region(d.dev, scull_nr_devs, scull_name);
	} else {
		result = alloc_chrdev_region(&d.dev, scull_minor, scull_nr_devs, scull_name);
		scull_major = MAJOR(d.dev);
	}

	if (result < 0)
		printk(KERN_WARNING "scull: can't get major %d\n", scull_major);

	return result;
}

static void reg_cdev(void)
{
	int err;

	cdev_init(&d.cdev, &scull_fops);
	d.cdev.owner = THIS_MODULE;
	d.cdev.ops = &scull_fops;
	err = cdev_add(&d.cdev, d.dev, scull_nr_devs);

	if (err)
		printk(KERN_WARNING "Error %d, adding scull %d", err, scull_nr_devs);
}

static int scull_trim(struct scull_dev *dev)
{
	struct scull_qset *next, *dptr;
	int qset = dev->qset;
	int i;
	for (dptr = dev->data; dptr; dptr = next) {
		if (dptr->data) {
			for (i = 0; i < qset; i++)
				kfree(dptr->data[i]);
			kfree(dptr->data);
			dptr->data = NULL;
		}
		next = dptr->next;
		kfree(dptr);
	}
	dev->size = 0;
	dev->quantum = scull_quantum;
	dev->qset = scull_qset;
	dev->data = NULL;
	return 0;
}

static int scull_open(struct inode *inode, struct file *filp)
{
	struct scull_dev *dev;

	dev = container_of(inode->i_cdev, struct scull_dev, cdev);
	filp->private_data = dev;

	if ( (filp->f_flags & O_ACCMODE) == O_WRONLY )
		scull_trim(dev);

	return 0;
}

static int scull_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t scull_read(struct file *filp, char __user *buf,
	size_t count, loff_t *f_pos)
{
	struct scull_dev *dev = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum;
	int qset = dev->qset;
	int itemsize = quantum * qset;
	int item, s_pos, q_pos, rest;
	
	ssize_t retval = 0;
/*
	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;*/
	if (*f_pos >= dev->size)
		goto out;
	if (*f_pos + count > dev->size)
		count = dev->size - *f_pos;

	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum;
	q_pos = rest % quantum;

	dptr = scull_follow(dev, item);

	if (! dptr || ! dptr->data || ! dptr->data[s_pos])
		goto out;

	if (count > quantum - q_pos)
		count = quantum - q_pos;

	if (copy_to_user(buf, dptr->data[s_pos] + q_pos, count)) {
		retval = -EFAULT;
		goto out;
	}

	*f_pos += count;
	retval = count;

out:
/*	up(&dev->sem);*/
	return retval;
}

static ssize_t scull_write(struct file *filp, const char __user *buf,
	size_t count, loff_t *f_pos)
{
	struct scull_dev *dev = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum;
	int qset = dev->qset;
	int itemsize = quantum * qset;
	int item, s_pos, q_pos, rest;

	ssize_t retval = -ENOMEM;

/*	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;*/

	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum;
	q_pos = rest % quantum;

	dptr = scull_follow(dev, item);

	if (! dptr)
		goto out;
	if (! dptr->data) {
		dptr->data = (void **)kmalloc(qset * sizeof(void *), GFP_KERNEL);
		if (! dptr->data)
			goto out;
		memset(dptr->data, 0, qset * sizeof(void *));
	}

	if (! dptr->data[s_pos]) {
		dptr->data[s_pos] = (void *)kmalloc(quantum, GFP_KERNEL);
		if (! dptr->data[s_pos])
			goto out;
		memset(dptr->data[s_pos], 0, quantum);
	}

	if (count > quantum - q_pos)
		count = quantum - q_pos;

	if (copy_from_user(dptr->data[s_pos] + q_pos, buf, count)) {
		retval = -EFAULT;
		goto out;
	}

	*f_pos += count;
	retval = count;

	if (dev->size < *f_pos)
		dev->size = *f_pos;

out:
/*	up(&dev->sem);*/
	return retval;
}

static struct scull_qset* scull_follow(struct scull_dev *dev, int item)
{
	struct scull_qset *ret = dev->data;
	if (! ret) {
		ret = dev->data = kmalloc(sizeof(struct scull_qset), GFP_KERNEL);
		if (! ret)
			return NULL;
		memset(ret, 0, sizeof(struct scull_qset));
	}

	while(item--)
		ret = ret->next;
	return ret;
}

static loff_t scull_llseek(struct file *f, loff_t off, int whence)
{
	struct scull_dev *dev = f->private_data;
	loff_t newpos;

	switch (whence) {
	case SEEK_SET:
		newpos = off;
		break;
	case SEEK_CUR:
		newpos = f->f_pos + off;
		break;
	case SEEK_END:
		newpos = dev->size + off;
		break;
	default:
		return -EINVAL;
	}

	if (newpos < 0)
		return -EINVAL;
	f->f_pos = newpos;
	return newpos;
}

static int scull_init(void)
{
	int rd = reg_dev();
	if (rd < 0)
		return rd;
	reg_cdev();
	printk(KERN_DEBUG "scull: i'm here: %s:%i\n", __FILE__, __LINE__);
	PDEBUG("scull: PDEBUG macro test %s\n", "kek");
	pr_info("scull: started");
	return 0;
}

static void scull_exit(void)
{
	cdev_del(&d.cdev);
	unregister_chrdev_region(d.dev, scull_nr_devs);
	scull_trim(&d);
	printk(KERN_NOTICE "scull: closed\n");

}

module_init(scull_init);
module_exit(scull_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ME");
MODULE_DESCRIPTION("SCULL");
MODULE_VERSION("0.0.1");
