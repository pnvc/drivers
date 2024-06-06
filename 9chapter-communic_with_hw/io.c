#include <linux/module.h>
#include <linux/init.h>

#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>

/* chapter 9 */
#include <linux/ioport.h>
#include <asm/io.h>

#define IO "io"
#define IOM "io: "
#define RET_SUCCESS 0
#define RET_FAILURE -1
#define NR_DEVICES 1
#define IO_START 0xa0000
#define IO_NR 0x100000 - IO_START
#define X "%X\n"
#define D "%d\n"
#define C "%c\n"
#define P "%p\n"
#define S "%s\n"

static int major = 0, minor = 0, use_mem = 0;

/* chapter 9 */
module_param(use_mem, int, S_IRUGO);

struct io {
	char cmd;
	dev_t dev;
	struct cdev cdev;
	struct class *class;
	struct file_operations fops;

	/* chapter 9 */
	struct resource *resource;
	void *iomem;
};

static int io_open(struct inode *, struct file *);
static ssize_t io_write(struct file *, const char __user *,
			size_t, loff_t *);
static ssize_t io_read(struct file *, char __user *,
			size_t, loff_t *);

static struct io io = {
	.fops = {
		.owner = THIS_MODULE,
		.write = io_write,
		.open = io_open,
		.read = io_read
	}
};

/* chapter 9 */
static int io_request_region(void)
{
	io.resource = request_region(IO_START, IO_NR, IO);
	if (!io.resource) {
		pr_info(IOM"failed io_request_region\n");
		return RET_FAILURE;
	}

	return RET_SUCCESS;
}

/* chapter 9 */
static int io_request_mem_region(void)
{
	/*
	io.resource = request_mem_region(IO_START, IO_NR, IO);
	if (!io.resource) {
		pr_info(IOM"failed io_request_mem_region\n");
		return RET_FAILURE;
	}
	*/
	io.iomem = ioremap(IO_START, IO_NR);
	pr_info(IOM P, io.iomem);

	return RET_SUCCESS;
}

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
		/* chapter 9 */
		if (use_mem) {
			int x;
			char str[10];
			void __iomem *add = io.iomem;
			iowrite16(0x3235, add);
			//memcpy_fromio(str, add, 2);
			pr_info(IOM S, str);
		} else {
			unsigned short a = 0;
			pr_info(IOM"cmd [ZERO]\n");
			outb_p(0x66, IO_START+0);
			wmb();
			a = inb_p(IO_START+0);
			rmb();
			pr_info(IOM"%x\n", a);
		}
		break;
	case '9':
		if (use_mem) {
			void __iomem *add = io.iomem;
			char str[10];
			memcpy_fromio(str, add, 2);
			pr_info(IOM S, str);
		}
	default:
		pr_info(IOM"cmd [%c]\n", iop->cmd);
		break;
	}

	return 1;
}

static ssize_t io_read(struct file *filp, char __user *buf,
			size_t count, loff_t *f_pos)
{
	ssize_t retval = 0;
	char kbuf[10];
	void __iomem *add = io.iomem;

	memcpy_fromio(kbuf, add, 2);
	pr_info(IOM S, kbuf);

	copy_to_user(buf, kbuf, 2);

	return count;
}


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

	return retval;
}


static int io_init(void)
{
	int err = 0;
	if (
		reg_dev()		|| /* get major */
		io_create_class()	|| /* create class */
		reg_cdev()		|| /* reg char device */
		io_device_create()	   /* create /dev/io */
	   )
		return RET_FAILURE;

			/* io mem region */	          /* io region */
	use_mem ? (err = io_request_mem_region()) : (err = io_request_region());
	if (err)
		return RET_FAILURE;

	pr_info(IOM"started. MAJOR [%d], MINOR [%d]\n", major, minor);

	return RET_SUCCESS;
}

static void io_exit(void)
{
	device_destroy(io.class, io.dev);
	class_destroy(io.class);
	unregister_chrdev_region(io.dev, NR_DEVICES);
	use_mem ?
		iounmap(io.iomem)
//		release_mem_region(IO_START, IO_NR)
		:
		release_region(IO_START, IO_NR);
	pr_info(IOM"closed\n");
}

module_init(io_init);
module_exit(io_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wbj0t");
MODULE_DESCRIPTION("9 chapter of ldd3");
MODULE_VERSION("0.0.0.1");
