#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>

#include "../lddbus.h"

#define KEK "kek"
#define KEKM "kek: "
#define SNL "%s\n"

static const char *v = "0.0.0.34";
static char name[] = "kek";

struct kek_dev {
	const char *msg;
	struct ldd_dev ldev;
};
#define to_kek_dev(dev) container_of(dev, struct kek_dev, ldev)

static ssize_t kek_show_ver(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ldd_dev *ld = to_ldd_dev(dev);
	struct kek_dev *kd = to_kek_dev(ld);
	return snprintf(buf, PAGE_SIZE, "%s\n", kd->msg);
}
static DEVICE_ATTR(ver, S_IRUGO, kek_show_ver, NULL);

static struct kek_dev kek;

static int register_kek_dev(struct kek_dev *keke)
{
	int err = 0;

	keke->ldev.name = name;
	keke->msg = v;
	err = register_ldd_dev(&keke->ldev);
	if (err)
		return err;

	if (device_create_file(&keke->ldev.dev, &dev_attr_ver))
		pr_info(KEKM SNL, "failed create kek device version file");

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
	device_unregister(&kek.ldev.dev);
}

module_init(kek_init);
module_exit(kek_exit);

MODULE_AUTHOR("ogokto");
MODULE_DESCRIPTION("kek device for the lddbus");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");
