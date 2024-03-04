#include <linux/module.h>
#include <linux/init.h>

#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/semaphore.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>
#include <linux/proc_fs.h>
#include <linux/ioctl.h>
#include <linux/sched.h>
#include <linux/wait.h>

#include "scullpipe.h"

/*----------------------------------------------------------------------------*/

#define SP 		"scullpipe"
#define SPMES 		SP ": [%s]\n"
#define SPERR 		SP ": failed [%s], return value [%i]\n"




/* general parameters */
#define DEFBUFSIZE 10
#define NR_DEVICES 1
#define RETSUCCESS 0
#define RET_FAILED -1

static int major = 0;
static int minor = 0;




/* main struct for the driver */
static struct scullpipe sp = {
	.bufsize = DEFBUFSIZE,
	.buf = NULL,
	.end = NULL,
	.rp = NULL,
	.wp = NULL,
	.fops = {
		.open = sp_open,
		.release = sp_release,
		.read = sp_read,
		.write =  sp_write
	},
	.dev_class = NULL
};




/* bufsize parameter and setter and getter for him */
const struct kernel_param_ops bufsize_param_ops = {
	.set = param_set_bufsize,
	.get = param_get_int
};

module_param_cb(bufsize, &bufsize_param_ops, &sp.bufsize, 0644);




/* definitions of the functions of the driver */
static int param_set_bufsize(const char *bs, const struct kernel_param *kp)
{
	int retval, old_bufsize;
	char *new_buf;

	if (down_interruptible(&sp.sem))
		return -ERESTARTSYS;

	old_bufsize = sp.bufsize;

	retval = param_set_int(bs, kp);
	if (retval) {
		pr_info(SPERR, "new buf size accepting", retval);
		sp.bufsize = old_bufsize;
		goto end;
	}
	pr_info(SP ": new buf size [%i] is accepted", sp.bufsize);

	new_buf = kmalloc(sp.bufsize, GFP_KERNEL);
	if (!new_buf) {
		retval = -ENOMEM;
		pr_info(SPERR, "new buf size setting", retval);
		sp.bufsize = old_bufsize;
		goto end;
	}
	kfree(sp.buf);
	sp.buf = new_buf;
	sp.end = sp.buf + sp.bufsize - 1;
	sp.rp = sp.wp = sp.buf;
	pr_info(SP ": new buf size [%i] is setted", sp.bufsize);

end:
	up(&sp.sem);
	return retval;
}

static int reg_dev(void)
{
	int retval;

	retval = alloc_chrdev_region(&sp.dev, minor, NR_DEVICES, SP);
	major = MAJOR(sp.dev);

	if (retval)
		pr_info(SPERR, "reg dev", retval);

	return retval;
}

static int reg_cdev(void)
{
	int retval;

	cdev_init(&sp.cdev, &sp.fops);
	sp.cdev.owner = THIS_MODULE;
	retval = cdev_add(&sp.cdev, sp.dev, 1);

	if (retval) {
		pr_info(SPERR, "reg cdev", retval);
		cdev_del(&sp.cdev);
		unregister_chrdev_region(sp.dev, NR_DEVICES);
	}

	return retval;
}

static int create_class_and_node(void)
{
	sp.dev_class = class_create(THIS_MODULE, SP);
	if (!sp.dev_class)
		goto failed_class_create;

	if (!device_create(sp.dev_class, NULL, sp.dev, NULL, SP))
		goto failed_device_create;

	goto success;

failed_device_create:
	class_destroy(sp.dev_class);
failed_class_create:
	unregister_chrdev_region(sp.dev, NR_DEVICES);

	return RET_FAILED;

success:
	return RETSUCCESS;
}

static void init_sema_and_queue(void)
{
	sema_init(&sp.sem, 1);
	init_waitqueue_head(&sp.inq);
	init_waitqueue_head(&sp.outq);
}

static int kmalloc_buf(void)
{
	sp.buf = (char*)kmalloc(sp.bufsize, GFP_KERNEL);
	if (!sp.buf) {
		pr_info(SPERR, "kmalloc buf", -ENOMEM);
		return -ENOMEM;
	}

	sp.wp = sp.rp = sp.buf;
	sp.end = sp.buf + sp.bufsize - 1;

	return RETSUCCESS;
}

/* file operation functinos */
static int spacefree(struct scullpipe *sppd)
{
	if (sppd->rp == sppd->wp)
		return sppd->bufsize - 1;
	return ((sppd->rp + sppd->bufsize - sppd->wp) % sppd->bufsize) - 1;
}

static int getwritespace(struct scullpipe *sppd, struct file *filp)
{
	while (!spacefree(sppd)) {
		DEFINE_WAIT(wait);

		up(&sppd->sem);

		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;

		pr_info(SPMES SPMES, "writing: going to sleep", current->comm);

		prepare_to_wait(&sppd->outq, &wait, TASK_INTERRUPTIBLE);

		if (!spacefree(sppd))
			schedule();

		finish_wait(&sppd->outq, &wait);

		if (signal_pending(current))
			return -ERESTARTSYS;

		if (down_interruptible(&sppd->sem))
			return -ERESTARTSYS;
	}
	return 0;
}

static int sp_open(struct inode *inode, struct file *filp)
{
	struct scullpipe *sppd;
       
	sppd = container_of(inode->i_cdev, struct scullpipe, cdev);
	filp->private_data = sppd;

	return RETSUCCESS;
}

static int sp_release(struct inode *inode, struct file *filp)
{
	return RETSUCCESS;
}

static ssize_t sp_read(struct file *filp, char __user *user_buf,
		size_t count, loff_t *offset)
{
	struct scullpipe *sppd;
       
	sppd = filp->private_data;

	if (down_interruptible(&sppd->sem))
		return -ERESTARTSYS;

	/* no data */
	while (sppd->rp == sppd->wp) {
		DEFINE_WAIT(wait);
		up(&sppd->sem);
		if (filp->f_flags & O_NONBLOCK)
			return -EAGAIN;
		pr_info(SPMES SP ": [%s] sleeps\n", "reading: going to sleep", current->comm);

		/*
		 * exclusive wait:
		 * every exclusive process woke up by principle FIFO
		 * and every nonexclusive process (if there are they)
		 * will be woke up and just one (first in the queue)
		 * exclusive waiter
		 */
		/*prepare_to_wait_exclusive(&sppd->inq, &wait, TASK_INTERRUPTIBLE);
		if (sppd->rp == sppd->wp)
			schedule();
		finish_wait(&sppd->inq, &wait);
		if (signal_pending(current))
			return -ERESTARTSYS;*/

		if (wait_event_interruptible(sppd->inq, (sppd->rp != sppd->wp)))
			return -ERESTARTSYS;
		if (down_interruptible(&sppd->sem))
			return -ERESTARTSYS;
	}

	/* data is there */
	if (sppd->wp > sppd->rp)
		count = min(count, (size_t)(sppd->wp - sppd->rp));
	else
		count = min(count, (size_t)(sppd->end - sppd->rp));

	if (copy_to_user(user_buf, sppd->rp, count)) {
		up(&sppd->sem);
		return -EFAULT;
	}

	sppd->rp += count;

	if (sppd->rp == sppd->end)
		sppd->rp = sppd->buf;

	up(&sppd->sem);

	wake_up_interruptible(&sppd->outq);

	pr_info(SP ": \"%s\" did read %li bytes\n", current->comm, (long)count);

	return count;
}

static ssize_t sp_write(struct file *filp, const char __user *user_buf,
		size_t count, loff_t *offset)
{
	struct scullpipe *sppd;
	int retval;
	
	sppd = filp->private_data;

	if (down_interruptible(&sppd->sem))
		return -ERESTARTSYS;

	retval = getwritespace(sppd, filp);
	if (retval)
		return retval;

	count = min(count, (size_t)spacefree(sppd));

	if (sppd->wp >= sppd->rp)
		count = min(count, (size_t)(sppd->end - sppd->wp));
	else
		count = min(count, (size_t)(sppd->rp - sppd->wp - 1));

	pr_info(SP": Going to accept %li bytes to %p from %p\n", (long)count, sppd->wp, sppd->buf);

	if (copy_from_user(sppd->wp, user_buf, count)) {
		up(&sppd->sem);
		return -EFAULT;
	}

	sppd->wp += count;

	if (sppd->wp == sppd->end)
		sppd->wp = sppd->buf;

	up(&sppd->sem);

	wake_up_interruptible(&sppd->inq);

	if (sppd->async_queue)
		kill_fasync(&sppd->async_queue, SIGIO, POLL_IN);

	pr_info(SP": %s did write %li bytes\n", current->comm, (long)count);

	return count;
}

static int scullpipe_init(void)
{
	init_sema_and_queue();
	if (kmalloc_buf())
		return -ENOMEM;
	if (reg_dev()) goto failed;
	if (create_class_and_node()) goto failed;
	if (reg_cdev()) goto failed;

	pr_info(SPMES, "inited");

	return RETSUCCESS;

failed:
	return RET_FAILED;
}

static void scullpipe_exit(void)
{
	device_destroy(sp.dev_class, sp.dev);
	class_destroy(sp.dev_class);
	cdev_del(&sp.cdev);
	unregister_chrdev_region(sp.dev, NR_DEVICES);
	pr_info(SPMES, "exited");
}

module_init(scullpipe_init);
module_exit(scullpipe_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wbj0t");
MODULE_DESCRIPTION("scull pipe :)");
MODULE_VERSION("0.0.2");
