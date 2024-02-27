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
#define DEFBUFSIZE 1000

static int major = 0;
static int minor = 0;
static int bufsize = DEFBUFSIZE;




/* main struct for the driver */
static struct scullpipe sp = {
	.bufsize = DEFBUFSIZE,
};




/* bufsize parameter and setter and getter for him */
static int set_bufsize(const char *bs, const struct kernel_param *kp)
{
	int retval, old_bufsize;
	char *old_buf, *old_end;

	retval = 0;
	old_bufsize = sp.bufsize;
	if (sp.buf) {
		old_buf = sp.buf;
		old_end = sp.end;
	}

	if (down_interruptible(&sp.sem))
		return -ERESTARTSYS;

	retval = param_set_int(bs, kp);
	if (retval) {
		pr_info(SPERR, "new buf size accepting", retval);
		sp.bufsize = old_bufsize;
		goto end;
	}
	pr_info(SP ": new buf size [%i] is accepted", sp.bufsize);

	sp.buf = kmalloc(sp.bufsize, GFP_KERNEL);
	if (!sp.buf) {
		retval = -ENOMEM;
		pr_info(SPERR, "new buf size setting", retval);
		sp.bufsize = old_bufsize;
		if (old_buf) {
			sp.buf = old_buf;
			sp.end = old_end;
		}
		goto end;
	}
	sp.end = sp.buf + sp.bufsize - 1;
	pr_info(SP ": new buf size [%i] is setted", sp.bufsize);
	kfree(old_buf);

end:
	up(&sp.sem);
	return retval;
}

const struct kernel_param_ops bufsize_param_ops = {
	.set = set_bufsize,
	.get = param_get_int
};
module_param_cb(bufsize, &bufsize_param_ops, &sp.bufsize, 0644);




/* definitions of the functions of the driver */
static int reg_dev(void)
{
	sp.buf = sp.end = NULL;
	sema_init(&sp.sem, 1);
	return 0;
}

static int reg_cdev(void)
{
	return 0;
}

static int scullpipe_init(void)
{
	int err;

	err = reg_dev();
	if (err) {
		pr_info(SPERR, "reg dev", err);
		return err;
	}

	err = reg_cdev();
	if (err)
		goto failed_reg_cdev;

	pr_info(SPMES, "inited");
	return 0;

failed_reg_cdev:
	return err;
}

static void scullpipe_exit(void)
{
	pr_info(SPMES, "exited");
}

module_init(scullpipe_init);
module_exit(scullpipe_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wbj0t");
MODULE_DESCRIPTION("scull pipe :)");
MODULE_VERSION("0.0.2");
