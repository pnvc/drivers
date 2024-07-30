#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>

#include "../lddbus.h"

#define KEK "kek"
#define KEKM "kek: "
#define SNL "%s\n"

static char v[] = "000.000.000.034";
static char name[] = "kek";

struct kek_dev {
	char *msg;
	struct ldd_dev ldev;
	struct device class_dev;
};
#define to_kek_dev(dev) container_of(dev, struct kek_dev, ldev)
#define to_kek_dev_from_class_dev(dev) container_of(dev, struct kek_dev, class_dev)

static ssize_t kek_show_ver(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ldd_dev *ld = to_ldd_dev(dev);
	struct kek_dev *kd = to_kek_dev(ld);
	return snprintf(buf, PAGE_SIZE, "%s\n", kd->msg);
}
static DEVICE_ATTR(ver, S_IRUGO, kek_show_ver, NULL);

static ssize_t kek_class_set_ver(struct device *dev, struct device_attribute *attr, const char *buf, size_t buf_size)
{
	return (ssize_t)strncpy(v, buf, strlen(v));
}
static ssize_t kek_class_show_ver(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct kek_dev *kd = to_kek_dev_from_class_dev(dev);
	return snprintf(buf, PAGE_SIZE, "%s\n", kd->msg);
}
static DEVICE_ATTR(version, 0664, kek_class_show_ver, kek_class_set_ver);

static struct kek_dev kek;

static int register_kek_dev(struct kek_dev *keke)
{
	int err = 0;

	keke->ldev.name = name;
	keke->msg = v;

	err = register_ldd_dev(&keke->ldev);
	if (err)
		return err;


	err = device_create_file(&keke->ldev.dev, &dev_attr_ver);
	if (err)
		pr_info(KEKM SNL, "failed create kek device version file");

	keke->class_dev.init_name = "kek_class";
	if (ldd_class_device_register(&kek.class_dev)) {
		if (err)
			device_remove_file(&keke->ldev.dev, &dev_attr_ver);
		device_unregister(&keke->ldev.dev);
		return -EFAULT;
	}

	if (device_create_file(&keke->class_dev, &dev_attr_version))
		pr_info(KEKM SNL, "failed create kek_class device set version file");

	return 0;
}

static int __init kek_init(void)
{
	pr_info(KEKM SNL, "init");
	return register_kek_dev(&kek);
}

static void __exit kek_exit(void)
{
	pr_info(KEKM SNL, "exit");
	device_remove_file(&kek.ldev.dev, &dev_attr_ver);
	device_unregister(&kek.ldev.dev);

	device_remove_file(&kek.class_dev, &dev_attr_version);
	device_unregister(&kek.class_dev);
}

module_init(kek_init);
module_exit(kek_exit);

MODULE_AUTHOR("ogokto");
MODULE_DESCRIPTION("kek device for the lddbus");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");
