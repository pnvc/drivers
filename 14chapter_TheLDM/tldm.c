#include <linux/module.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/delay.h>

/* chapter 14 the LDM */
#include <linux/kobject.h>
#include <linux/sysfs.h>

#define TLDM  "tldm"
#define TLDMM "tldm: "

static int major = 0;
static int minor = 0;



struct tldm {
	/* chapter 14 TheLDM */
	struct kobject kobj;
	int kobj_count;

	char cmd;
	dev_t dev;
	struct cdev cdev;
	struct class *class;
	struct file_operations fops;
};

/* chapter 14 */
struct tldm2 {
	struct kobject kobj;
	char cmd;
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

static struct tldm2 tldm2 = {
	.cmd = 0
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
#define to_tldm(map) container_of(map, struct tldm, kobj);
#define to_tldm2(map) container_of(map, struct tldm2, kobj);
#define TLDMKO "tldm_kobj"
static void tldm_kobj_type_release(struct kobject *);
static void tldm_kobj_type_release2(struct kobject *);

/* sysfs attrs and show/store */
static struct attribute tldm_kobj_attr = {
	.name = "pesos",
	.mode = 0644
};
static struct attribute *tldm_kobj_attrs[] = {
	&tldm_kobj_attr,
	NULL
};
static struct attribute_group tldm_kobj_attr_group = {
	.attrs = tldm_kobj_attrs
};
static const struct attribute_group *tldm_kobj_attr_groups[] = {
	&tldm_kobj_attr_group,
	NULL
};
static ssize_t tldm_kobj_sysfs_show(struct kobject *kobj, struct attribute *attr,
		    char *buffer);
static ssize_t tldm_kobj_sysfs_store(struct kobject *kobj, struct attribute *attr,
		    const char *buffer, size_t size);
static struct sysfs_ops tldm_kobj_sysfs_ops = {
	.show = tldm_kobj_sysfs_show,
	.store = tldm_kobj_sysfs_store
};
static ssize_t tldm_kobj_sysfs_show(struct kobject *kobj, struct attribute *attr,
				    char *buffer)
{
	struct tldm *tldm_tmp = to_tldm(kobj);
	return sysfs_emit(buffer, "%d\n", tldm_tmp->cmd);
}
static ssize_t tldm_kobj_sysfs_store(struct kobject *kobj, struct attribute *attr,
				     const char *buffer, size_t size)
{
	struct tldm *tldm_tmp = to_tldm(kobj);
	int ret;
	int i;

	ret = kstrtoint(buffer, 10, &i);
	if (ret < 0)
		return ret;
	tldm_tmp->cmd = (char)i;

	return size;
}

static struct kobj_type tldm_kobj_type = {
	.release = tldm_kobj_type_release,
	.sysfs_ops = &tldm_kobj_sysfs_ops,
	.default_groups = tldm_kobj_attr_groups

};

static struct kset *tldm_kset;

static int tldm_kobj_init(void)
{
	memset(&tldm.kobj, 0, sizeof(struct kobject));
/*
	kobject_init(&tldm.kobj, &tldm_kobj_type);

	if (kobject_add(&tldm.kobj, NULL, TLDMKO) < 0) {
		kobject_put(&tldm.kobj);
		return -1;
	}

	kobject_uevent(&tldm.kobj, KOBJ_ADD);

	tldm.kobj_count = 1;
*/

	tldm_kset = kset_create_and_add("tldm_kset", NULL, NULL);
	if (!tldm_kset)
		return -ENOMEM;

	return 0;
}


static void tldm_kobj_type_release(struct kobject *kobj)
{
	struct tldm *ttldm = to_tldm(kobj);
	pr_info(TLDMM"kobj released\n");
}
static void tldm_kobj_type_release2(struct kobject *kobj)
{
	struct tldm2 *ttldm2 = to_tldm2(kobj);
	pr_info(TLDMM"kobj 2 released\n");
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

	/* chapter 14 */
	kset_unregister(tldm_kset);

	pr_info(TLDMM"exited\n");
}

module_init(tldm_init);
module_exit(tldm_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("nclud");
MODULE_DESCRIPTION("chapter 14 The Linux Device Model");
MODULE_VERSION("0.0.0.1");
