#include <linux/module.h>
#include <linux/init.h>

#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>

/* chapter 13 USB */
#include <linux/usb.h>

#define LUSB "lusb"
#define LUSBM "lusb: "

#define RET_SUCCESS 0
#define RET_FAILURE 1

#define NR_DEVICES 1

static int major = 0, minor = 0, use_mem = 0;
module_param(use_mem, int, S_IRUGO);

struct lusb {
	char cmd;
	dev_t dev;
	struct cdev cdev;
	struct class *class;
	struct file_operations fops;
};

static int lusb_open(struct inode *, struct file *);
static ssize_t lusb_write(struct file *, const char __user *,
			size_t, loff_t *);
static ssize_t lusb_read(struct file *, char __user *,
			size_t, loff_t *);

static struct lusb lusb = {
	.fops = {
		.owner = THIS_MODULE,
		.write = lusb_write,
		.open = lusb_open,
		.read = lusb_read
	}
};

static int lusb_open(struct inode *inode, struct file *filp)
{
	struct lusb *lusbp = container_of(inode->i_cdev, struct lusb, cdev);
	filp->private_data = lusbp;
	return 0;
}

static ssize_t lusb_write(struct file *filp, const char __user *buf,
			size_t count, loff_t *f_pos)
{
	struct lusb *lusbp = filp->private_data;

	if (get_user(lusbp->cmd, buf) != 0)
		return -EFAULT;

	switch(lusbp->cmd) {
	default:
		pr_info(LUSBM"cmd [%c]\n", lusbp->cmd);
		break;
	}

	return 1;
}

static ssize_t lusb_read(struct file *filp, char __user *buf,
			size_t count, loff_t *f_pos)
{
	return count;
}


static int lusb_device_create(void)
{
	if (!device_create(lusb.class, NULL, lusb.dev, NULL, LUSB)) {
		pr_info(LUSBM"failed lusb_device_create\n");
		return RET_FAILURE;
	}

	return RET_SUCCESS;
}

static int reg_cdev(void)
{
	int retval = 0;

	cdev_init(&lusb.cdev, &lusb.fops);
	lusb.cdev.owner = THIS_MODULE;
	retval = cdev_add(&lusb.cdev, lusb.dev, 1);

	if (retval) {
		pr_info(LUSBM"failed reg_cdev, err = %d\n", retval);
		cdev_del(&lusb.cdev);
		unregister_chrdev_region(lusb.dev, NR_DEVICES);
	}

	return retval;
}

static int lusb_create_class(void)
{
	lusb.class = class_create(LUSB);
	if (!lusb.class) {
		pr_info(LUSBM"failed lusb_create_class\n");
		goto reterr;
	}

	return RET_SUCCESS;

reterr:
	class_destroy(lusb.class);
	return -ENOMEM;
}

static int reg_dev(void)
{
	int retval = 0;

	retval = alloc_chrdev_region(&lusb.dev, minor, NR_DEVICES, LUSB);
	major = MAJOR(lusb.dev);

	if (retval)
		pr_info(LUSBM"failed reg_dev, err = %d\n", retval);

	return retval;
}

/* chapter 13 USB */
#define USB_SKEL_VENDOR_ID 0xfff0
#define USB_SKEL_PRODUCT_ID 0xfff0

static struct usb_device_id skel_table[] = {
	{
		USB_DEVICE(USB_SKEL_VENDOR_ID, USB_SKEL_PRODUCT_ID)
	},
	{}
};
//MODULE_DEVICE_TABLE(usb, skel_table);

/* for every USB device in the system, just set driver_info field */
static struct usb_device_id usb_ids[] = {
	{ .driver_info = 42 },
	{}
};
MODULE_DEVICE_TABLE(usb, usb_ids);

static int lusb_probe(struct usb_interface *intf, const struct usb_device_id *id)
{

	return 0;
}
static void lusb_disconnect(struct usb_interface *intf)
{
	return  ;
}

struct usb_driver lusb_usb_driver = {
	//.owner = THIS_MODULE,
	.name = LUSB,
	.id_table = usb_ids,
	.probe = lusb_probe,
	.disconnect = lusb_disconnect
};


static int lusb_init(void)
{
	if (
		reg_dev()		|| /* get major */
		lusb_create_class()	|| /* create class */
		reg_cdev()		|| /* reg char device */
		lusb_device_create()	   /* create /dev/lusb */
	   )
		return RET_FAILURE;

	int result = usb_register(&lusb_usb_driver);
	if (result) {
		pr_info(LUSBM"failed usb_register, %d\n", result);
		return result;
	}

	/* chapter 13 USB */
	pr_info(LUSBM"started. MAJOR [%d], MINOR [%d]\n", major, minor);

	return RET_SUCCESS;
}

static void lusb_exit(void)
{
	device_destroy(lusb.class, lusb.dev);
	class_destroy(lusb.class);
	unregister_chrdev_region(lusb.dev, NR_DEVICES);

	/* chapter 13 USB */
	usb_deregister(&lusb_usb_driver);

	pr_info(LUSBM"closed\n");
}

module_init(lusb_init);
module_exit(lusb_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wbj0t");
MODULE_DESCRIPTION("13 chapter of ldd3");
MODULE_VERSION("0.0.0.1");
