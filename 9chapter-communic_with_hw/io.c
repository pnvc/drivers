#include <linux/module.h>
#include <linux/init.h>

#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>

#define IO "io"
#define IOM "io: "
#define RET_SUCCESS 0
#define RET_FAILURE -1
#define NR_DEVICES 1

static int major = 0, minor = 0;

struct io {
	char cmd;
	dev_t dev;
	struct cdev cdev;
	struct class *class;
	struct file_operations fops;
};

static int io_open(struct inode *inode, struct file *filp)
{
	struct io *iop = container_of(inode->i_cdev, struct io, cdev);
	filp->private_data = iop;
	return 0;
}

static ssize_t io_write(struct file *filp, const char __user *buf,
			size_t count, loff_t *f_pos)
{
	struct io *iop = filp->private_data;

	if (get_user(iop->cmd, buf) != 0)
		return -EFAULT;

	switch(iop->cmd) {
	case '0':
		pr_info(IOM"ZERO\n");
		break;
	default:
		pr_info(IOM"%c\n", iop->cmd);
		break;
	}

	return 1;
}

static struct io io = {
	.fops = {
		.owner = THIS_MODULE,
		.write = io_write,
		.open = io_open,
	}
};

static int io_device_create(void)
{
	if (!device_create(io.class, NULL, io.dev, NULL, IO)) {
		pr_info(IOM"failed io_device_create\n");
		return RET_FAILURE;
	}

	return RET_SUCCESS;
}

static int reg_cdev(void)
{
	int retval = 0;

	cdev_init(&io.cdev, &io.fops);
	io.cdev.owner = THIS_MODULE;
	retval = cdev_add(&io.cdev, io.dev, 1);

	if (retval) {
		pr_info(IOM"failed reg_cdev, err = %d\n", retval);
		cdev_del(&io.cdev);
		unregister_chrdev_region(io.dev, NR_DEVICES);
	}

	return retval;
}

static int io_create_class(void)
{
	io.class = class_create(IO);
	if (!io.class) {
		pr_info(IOM"failed io_create_class\n");
		goto reterr;
	}

	return RET_SUCCESS;

reterr:
	class_destroy(io.class);
	return -ENOMEM;
}

static int reg_dev(void)
{
	int retval = 0;

	retval = alloc_chrdev_region(&io.dev, minor, NR_DEVICES, IO);
	major = MAJOR(io.dev);

	if (retval)
		pr_info(IOM"failed reg_dev, err = %d\n", retval);
	else
		pr_info(IOM"major %d, minor %d\n", major, minor);

	return retval;
}


static int io_init(void)
{
	if (
		reg_dev()		||
		io_create_class()	||
		reg_cdev()		||
		io_device_create()
	   )
		return RET_FAILURE;

	pr_info(IOM"started\n");

	return RET_SUCCESS;
}

static void io_exit(void)
{
	device_destroy(io.class, io.dev);
	class_destroy(io.class);
	unregister_chrdev_region(io.dev, NR_DEVICES);
	pr_info(IOM"closed\n");
}

module_init(io_init);
module_exit(io_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wbj0t");
MODULE_DESCRIPTION("9 chapter of ldd3");
MODULE_VERSION("0.0.0.1");
