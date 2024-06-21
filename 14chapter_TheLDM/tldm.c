#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/delay.h>

#define TLDM  "tldm"
#define TLDMM "tldm: "

static int major = 0;
static int minor = 0;

struct tldm {
	char cmd;
	dev_t dev;
	struct cdev cdev;
	struct class *class;
	struct file_operations fops;
};

static int tldm_open(struct inode *, struct file *);
static ssize_t tldm_read(struct file *, char __user *, size_t, loff_t *);
static ssize_t tldm_write(struct file *, const char __user *, size_t, loff_t *);

static struct tldm tldm = {
	.cmd = 0,
	.class = NULL,
	.fops = {
		.owner = THIS_MODULE,
		.open = tldm_open,
		.read = tldm_read,
		.write = tldm_write
	}
};

static int tldm_open(struct inode *inode, struct file *filp)
{
	return 0;
}

static ssize_t tldm_read(struct file *filp, char __user *user_buf, size_t count,
		loff_t *offset)
{
	if (put_user(tldm.cmd, user_buf))
		return -EFAULT;

	return 1;
}

static ssize_t tldm_write(struct file *filp, const char __user *user_buf, 
		size_t count, loff_t *offset)
{
	if (get_user(tldm.cmd, user_buf))
		return -EFAULT;

	switch(tldm.cmd) {
	default:
		pr_info(TLDMM"default cmd: 0x%X\n", tldm.cmd);
	}

	return 1;
}

/* chapter 14 The Linux Device Model */
#define TLDMKO "tldm_kobj"
static void tldm_kobj_type_release(struct kobject *);
static struct kobject tldm_kobj;
static struct kobj_type tldm_kobj_type = {
	.release = tldm_kobj_type_release
};
static int tldm_kobj_init(void)
{
	memset(&tldm_kobj, 0, sizeof(struct kobject));

	kobject_init(&tldm_kobj, &tldm_kobj_type);

	kobject_add(&tldm_kobj, NULL, TLDMKO);

	return 0;
}

static void tldm_kobj_type_release(struct kobject *kobj)
{
	pr_info(TLDMM"kobj released\n");
	return;
}

static int __init tldm_init(void)
{
	int retval = 0;

	/* get dev_t */
	retval = alloc_chrdev_region(&tldm.dev, minor, 1, TLDM);
	major = MAJOR(tldm.dev);
	if (retval) {
		pr_info(TLDMM"failed alloc_chrdev_region\n");
		return -EFAULT;
	}
	pr_info(TLDMM"dev_t: M %d, m %d\n", MAJOR(tldm.dev), MINOR(tldm.dev));

	/* create class */
	tldm.class = class_create(TLDM);
	if (!tldm.class) {
		pr_info(TLDMM"failed class_create\n");
		return -ENOMEM;
	}
	pr_info(TLDMM"class created\n");

	/* init/add cdev */
	cdev_init(&tldm.cdev, &tldm.fops);
	tldm.cdev.owner = THIS_MODULE;
	retval = cdev_add(&tldm.cdev, tldm.dev, 1);
	if (retval) {
		pr_info(TLDMM"failed cdev_add\n");
		cdev_del(&tldm.cdev);
		unregister_chrdev_region(tldm.dev, 1);
		return retval;
	}
	pr_info(TLDMM"cdev inited and added\n");

	/* create device in fs */
	if (!device_create(tldm.class, NULL, tldm.dev, NULL, TLDM)) {
		pr_info(TLDMM"failed device_create\n");
		class_destroy(tldm.class);
		cdev_del(&tldm.cdev);
		unregister_chrdev_region(tldm.dev, 1);
		return -EFAULT;
	}

	if (tldm_kobj_init()) {
		device_destroy(tldm.class, tldm.dev);
		class_destroy(tldm.class);
		cdev_del(&tldm.cdev);
		unregister_chrdev_region(tldm.dev, 1);
		return -EFAULT;
	}

	pr_info(TLDMM"device created\n");

	pr_info(TLDMM"inited\n");

	return 0;
}

static void __exit tldm_exit(void)
{
	device_destroy(tldm.class, tldm.dev);
	class_destroy(tldm.class);
	cdev_del(&tldm.cdev);
	unregister_chrdev_region(tldm.dev, 1);
	kobject_put(&tldm_kobj);
	pr_info(TLDMM"exited\n");
}

module_init(tldm_init);
module_exit(tldm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nclud");
MODULE_DESCRIPTION("chapter 14 The Linux Device Model");
MODULE_VERSION("0.0.0.1");
