#include <linux/module.h>
#include <linux/init.h>
#include <linux/moduleparam.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/semaphore.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/ioctl.h>
#include <linux/sched.h>
#include <linux/wait.h>
#include "scull_main.h"

#include <linux/mm.h>
#include <linux/highmem.h>

#define SCULL_QUANTUM 	4000
#define SCULL_QSET	1000
#define SCULL_NR_DEVS	4
#define SCULL_MAJOR	0
#define SCULL_MINOR	0
#define SCULL_NAME	"scull"

static int scull_major = SCULL_MAJOR;
static int scull_minor = SCULL_MINOR;
static int scull_nr_devs = SCULL_NR_DEVS;
static int scull_quantum = SCULL_QUANTUM;
static int scull_qset = SCULL_QSET;
static char *scull_name = SCULL_NAME;
module_param(scull_major, int, S_IRUGO);
module_param(scull_minor, int, S_IRUGO);
module_param(scull_nr_devs, int, S_IRUGO);
module_param(scull_quantum, int, S_IRUGO);
module_param(scull_qset, int, S_IRUGO);

/* -------------------------------- */

static struct scull_dev d = {
	.node = {
		{ .size = 0, .data = NULL, .general_offset = 0 },
		{ .size = 0, .data = NULL, .general_offset = 0 },
		{ .size = 0, .data = NULL, .general_offset = 0 },
		{ .size = 0, .data = NULL, .general_offset = 0 },
	}
		
};

static struct file_operations scull_fops = {
	.owner = THIS_MODULE,
	.llseek = scull_llseek,
	.read = scull_read,
	.write = scull_write,
	.open = scull_open,
	.release = scull_release,
	.unlocked_ioctl = ioctl,
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
	int i;

	for (i = 0; i < scull_nr_devs; i++) {
		d.node[i].quantum = scull_quantum;
		d.node[i].qset = scull_qset;
		sema_init(&d.node[i].sem, 1);
		cdev_init(&d.node[i].cdev, &scull_fops);
		d.node[i].cdev.owner = THIS_MODULE;
		err = cdev_add(&d.node[i].cdev, d.dev + i, 1);
		if (err)
			printk(KERN_WARNING "Error %d, adding scull %d", err, scull_nr_devs);
	}
}

static int scull_trim(void)
{
	struct scull_qset *next, *dptr;
	int qset = scull_qset;
	int i, j;

	for (i = 0; i < scull_nr_devs; i++) {
		for (dptr = d.node[i].data; dptr; dptr = next) {
			if (dptr->data) {
				for (j = 0; j < qset; j++)
					kfree(dptr->data[j]);
				kfree(dptr->data);
			}
			next = dptr->next;
			kfree(dptr);
		}
	}

	return 0;
}

static int scull_open(struct inode *inode, struct file *filp)
{
	struct scull_cdev *scd;

	scd = container_of(inode->i_cdev, struct scull_cdev, cdev);
	filp->private_data = scd;

	return 0;
}

static int scull_release(struct inode *inode, struct file *filp)
{
	return 0;
}

static DECLARE_WAIT_QUEUE_HEAD(wq);
static int flag = 0;

static void *addr = NULL;
static struct page *pg = NULL;
static void *pg_kmap = NULL;
static unsigned long pg_offset = 0;
static ssize_t scull_read(struct file *filp, char __user *buf,
	size_t count, loff_t *f_pos)
{
	struct scull_cdev *scd = filp->private_data;
	struct scull_qset *qsptr;
	int quantum = scd->quantum;
	int qset = scd->qset;
	int item, s_pos, q_pos, rest;
	unsigned long itemsize = quantum * qset;

	if (pg_kmap) {
		*(char*)(pg_kmap + pg_offset) = '8';
		kunmap(pg_kmap);
		pg_kmap = NULL;
	}
	
	ssize_t retval = 0;

	wait_event_interruptible(wq, flag);
	flag = 0;

	if (down_interruptible(&scd->sem))
		return -ERESTARTSYS;
	if (*f_pos >= scd->general_offset)
		goto out;
	if (*f_pos + count > scd->general_offset)
		count = scd->general_offset - *f_pos;

	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum;
	q_pos = rest % quantum;

	qsptr = scull_follow(scd, item);

	if (! qsptr || ! qsptr->data || ! qsptr->data[s_pos])
		goto out;

	if (count > quantum - q_pos)
		count = quantum - q_pos;

	if (copy_to_user(buf, qsptr->data[s_pos] + q_pos, count)) {
		retval = -EFAULT;
		goto out;
	}

	*f_pos += count;
	retval = count;

out:
	up(&scd->sem);
	return retval;
}

static ssize_t scull_write(struct file *filp, const char __user *buf,
	size_t count, loff_t *f_pos)
{
	struct scull_cdev *dev = filp->private_data;
	struct scull_qset *dptr;
	int quantum = dev->quantum;
	int qset = dev->qset;
	int itemsize = quantum * qset;
	int item, s_pos, q_pos, rest;
	ssize_t retval = -ENOMEM;

	pg = virt_to_page(buf);
	if (pg) {
		addr = page_address(pg);
		pg_kmap = kmap(pg);
		if (addr) {
			pg_offset = __pa(buf) - __pa(addr);
			*(char *)(pg_kmap + pg_offset) = '8';
			if (pg_kmap) {
				pr_info("write buf %p, page %p\n\
					page addr %p, page kmap addr %p\n\
					PA buf %lx, PA page addr %lx\n",
					buf, pg, addr, pg_kmap, __pa(buf), __pa(addr));
				kunmap(pg_kmap);
			}
		}
	}

	*f_pos = dev->general_offset;

	if (count >= itemsize << 1)
		goto out;

	if (down_interruptible(&dev->sem))
		return -ERESTARTSYS;

	item = (long)*f_pos / itemsize;
	rest = (long)*f_pos % itemsize;
	s_pos = rest / quantum;
	q_pos = rest % quantum;

	dptr = scull_follow_for_write(dev, item);

	if (!dptr) {
		goto out;
	}

	if (!dptr->data) {
		dptr->data = (void **)kmalloc(qset * sizeof(void *), GFP_KERNEL);
		if (! dptr->data)
			goto out;
		memset(dptr->data, 0, qset * sizeof(void *));
	}

	if (!dptr->data[s_pos]) {
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

	flag = 1;
	wake_up_interruptible(&wq);

	retval = count;
	dev->general_offset += count;

	if (dev->size < *f_pos)
		dev->size = *f_pos;

out:
	up(&dev->sem);
	return retval;
}

static struct scull_qset* scull_follow(struct scull_cdev *cdev, int item)
{
	struct scull_qset *ret = cdev->data;
	while(item-- && ret)
		ret = ret->next;
	return ret;
}

static struct scull_qset* scull_follow_for_write
(struct scull_cdev *cdev, int item)
{
	struct scull_qset *ret = cdev->data;
	if (!ret) {
		ret = cdev->data = kmalloc(sizeof(struct scull_qset),
						GFP_KERNEL);
		if (ret) {
			pr_info("scull: im here\n");
			memset(ret, 0, sizeof(struct scull_qset));
		}
	}

	if (ret) {
		while (item--) {
			if (!ret->next) {
				ret->next = kmalloc(sizeof(struct scull_qset),
							GFP_KERNEL);
				if (!ret->next)
					item = 0;
			}
			ret = ret->next;
		}
	}

	return ret;
}

static loff_t scull_llseek(struct file *f, loff_t off, int whence)
{
	struct scull_cdev *dev = f->private_data;
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

/*
 * S 'set'
 * T 'tell'
 * G 'get' by pointer
 * Q 'query' by return value
 * X 'eXchange' switch S and G atomically
 * H 'sHift' switch T and Q atomically
 */

#define SCULL_IOC_MN 0xC7

#define SCULL_IOCRESET		_IO(SCULL_IOC_MN, 0)
#define SCULL_IOCSQUANTUM	_IOW(SCULL_IOC_MN, 1, int)
#define SCULL_IOCSQSET		_IOW(SCULL_IOC_MN, 2, int)
#define SCULL_IOCTQUANTUM	_IO(SCULL_IOC_MN, 3)
#define SCULL_IOCTQSET		_IO(SCULL_IOC_MN, 4)
#define SCULL_IOCGQUANTUM	_IOR(SCULL_IOC_MN, 5, int)
#define SCULL_IOCGQSET		_IOR(SCULL_IOC_MN, 6, int)
#define SCULL_IOCQQUANTUM	_IO(SCULL_IOC_MN, 7)
#define SCULL_IOCQQSET		_IO(SCULL_IOC_MN, 8)
#define SCULL_IOCXQUANTUM	_IOWR(SCULL_IOC_MN, 9, int)
#define SCULL_IOCXQSET		_IOWR(SCULL_IOC_MN, 10, int)
#define SCULL_IOCHQUANTUM	_IO(SCULL_IOC_MN, 11)
#define SCULL_IOCHQSET		_IO(SCULL_IOC_MN, 12)

#define SCULL_IOC_MAXNR 12


static long ioctl(struct file *fp,
		unsigned int cmd, unsigned long arg)
{
	int err = 0, tmp;
	int retval;

	/* check type and command number with masks */
	if (_IOC_TYPE(cmd) != SCULL_IOC_MN)
		return -ENOTTY;
	if (_IOC_NR(cmd) > SCULL_IOC_MAXNR)
		return -ENOTTY;

	if (_IOC_DIR(cmd) & _IOC_READ || _IOC_DIR(cmd) & _IOC_WRITE)
		err = !access_ok((void __user *)arg, _IOC_SIZE(cmd));
	if (err)
		return -EFAULT;

	switch (cmd) {

	case SCULL_IOCRESET:
		scull_quantum = SCULL_QUANTUM;
		scull_qset = SCULL_QSET;
		break;

	case SCULL_IOCSQUANTUM:
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		retval = __get_user(scull_quantum, (int __user *)arg);
		break;

	case SCULL_IOCTQUANTUM:
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		scull_quantum = arg;
		break;

	case SCULL_IOCGQUANTUM:
		retval = __put_user(scull_quantum, (int __user *)arg);
		break;

	case SCULL_IOCQQUANTUM:
		return scull_quantum;
		break;

	case SCULL_IOCXQUANTUM:
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		tmp = scull_quantum;
		retval = __get_user(scull_quantum, (int __user *)arg);
		if (retval == 0)
			retval = __put_user(tmp, (int __user *)arg);
		break;

	case SCULL_IOCHQUANTUM:
		if (!capable(CAP_SYS_ADMIN))
			return -EPERM;
		tmp = scull_quantum;
		scull_quantum = arg;
		return tmp;

	default:
		return -ENOTTY;
	}

	return retval;
}

static int scull_init(void)
{
	int rd = reg_dev();
	if (rd < 0)
		return rd;
	reg_cdev();
	pr_info("scull: started");
	return 0;
}

static void scull_exit(void)
{
	for (int i = 0; i < scull_nr_devs; i++)
		cdev_del(&d.node[i].cdev);
	unregister_chrdev_region(d.dev, scull_nr_devs);
	scull_trim();
	printk(KERN_NOTICE "scull: closed\n");
}

module_init(scull_init);
module_exit(scull_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("ME");
MODULE_DESCRIPTION("SCULL");
MODULE_VERSION("0.0.1");
