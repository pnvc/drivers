#include <linux/module.h>
#include <linux/init.h>

#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/cdev.h>

/* chapter 12 PCI */
#include <linux/pci.h>

#define LPCI "lpci"
#define LPCIM "lpci: "

#define RET_SUCCESS 0
#define RET_FAILURE 1

#define NR_DEVICES 1

static int major = 0, minor = 0, use_mem = 0;
module_param(use_mem, int, S_IRUGO);

struct lpci {
	char cmd;
	dev_t dev;
	struct cdev cdev;
	struct class *class;
	struct file_operations fops;
};

static int lpci_open(struct inode *, struct file *);
static ssize_t lpci_write(struct file *, const char __user *,
			size_t, loff_t *);
static ssize_t lpci_read(struct file *, char __user *,
			size_t, loff_t *);

static struct lpci lpci = {
	.fops = {
		.owner = THIS_MODULE,
		.write = lpci_write,
		.open = lpci_open,
		.read = lpci_read
	}
};

static int lpci_open(struct inode *inode, struct file *filp)
{
	struct lpci *lpcip = container_of(inode->i_cdev, struct lpci, cdev);
	filp->private_data = lpcip;
	return 0;
}

static ssize_t lpci_write(struct file *filp, const char __user *buf,
			size_t count, loff_t *f_pos)
{
	struct lpci *lpcip = filp->private_data;

	if (get_user(lpcip->cmd, buf) != 0)
		return -EFAULT;

	switch(lpcip->cmd) {
	default:
		pr_info(LPCIM"cmd [%c]\n", lpcip->cmd);
		break;
	}

	return 1;
}

static ssize_t lpci_read(struct file *filp, char __user *buf,
			size_t count, loff_t *f_pos)
{
	return count;
}


static int lpci_device_create(void)
{
	if (!device_create(lpci.class, NULL, lpci.dev, NULL, LPCI)) {
		pr_info(LPCIM"failed lpci_device_create\n");
		return RET_FAILURE;
	}

	return RET_SUCCESS;
}

static int reg_cdev(void)
{
	int retval = 0;

	cdev_init(&lpci.cdev, &lpci.fops);
	lpci.cdev.owner = THIS_MODULE;
	retval = cdev_add(&lpci.cdev, lpci.dev, 1);

	if (retval) {
		pr_info(LPCIM"failed reg_cdev, err = %d\n", retval);
		cdev_del(&lpci.cdev);
		unregister_chrdev_region(lpci.dev, NR_DEVICES);
	}

	return retval;
}

static int lpci_create_class(void)
{
	lpci.class = class_create(LPCI);
	if (!lpci.class) {
		pr_info(LPCIM"failed lpci_create_class\n");
		goto reterr;
	}

	return RET_SUCCESS;

reterr:
	class_destroy(lpci.class);
	return -ENOMEM;
}

static int reg_dev(void)
{
	int retval = 0;

	retval = alloc_chrdev_region(&lpci.dev, minor, NR_DEVICES, LPCI);
	major = MAJOR(lpci.dev);

	if (retval)
		pr_info(LPCIM"failed reg_dev, err = %d\n", retval);

	return retval;
}

/* chapter 12 PCI */
struct lpci_pci {
	int lp;
	char pl;
} __attribute__ ((packed));

static struct lpci_pci lpci_pci = {
	.lp = 12,
	.pl = 21
};

static const struct pci_device_id lpci_pci_ids[] = {
	{
		//PCI_DEVICE_CLASS(0x999, 0x666), ; with this no in modules.alias
		PCI_DEVICE(0x666, 0x999),
		.driver_data = (unsigned long)&lpci_pci
	},
	{}
};

MODULE_DEVICE_TABLE(pci, lpci_pci_ids);

static int lpci_pci_probe(struct pci_dev *dev, const struct pci_device_id *id)
{
	u16 rw, ww;
	if (pci_enable_device(dev))
		return -EFAULT;

	/* no deal with byte ordering */
	if (pci_read_config_word(dev, 0, &rw))
		return -EFAULT;

	if (pci_write_config_word(dev, 2, ww))
		return -EFAULT;



	pr_info(LPCIM"%d\n", ((const struct lpci_pci*)(id->driver_data))->lp);
	return 0;
}

static void lpci_pci_remove(struct pci_dev *dev)
{
	return;
}

static struct pci_driver lpci_pci_driver = {
	.name = LPCI,
	.id_table = lpci_pci_ids,
	.probe = lpci_pci_probe,
	.remove = lpci_pci_remove,
};


static int lpci_init(void)
{
	if (
		reg_dev()		|| /* get major */
		lpci_create_class()	|| /* create class */
		reg_cdev()		|| /* reg char device */
		lpci_device_create()	   /* create /dev/lpci */
	   )
		return RET_FAILURE;

	/* chapter 12 PCI */
	if (pci_register_driver(&lpci_pci_driver))
		return RET_FAILURE;

	pr_info(LPCIM"started. MAJOR [%d], MINOR [%d]\n", major, minor);

	return RET_SUCCESS;
}

static void lpci_exit(void)
{
	device_destroy(lpci.class, lpci.dev);
	class_destroy(lpci.class);
	unregister_chrdev_region(lpci.dev, NR_DEVICES);
	/* chapter 12 PCI */
	pci_unregister_driver(&lpci_pci_driver);

	pr_info(LPCIM"closed\n");
}

module_init(lpci_init);
module_exit(lpci_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("wbj0t");
MODULE_DESCRIPTION("12 chapter of ldd3");
MODULE_VERSION("0.0.0.1");
