#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>

#include "../lddbus.h"

#define KEK "lol"
#define KEKM "lol: "
#define SNL "%s\n"

static const char *v = "0.0.0.34";
static char name[] = "lol";

struct lol_dev {
	const char *msg;
	struct ldd_dev ldev;
};
#define to_lol_dev(dev) container_of(dev, struct lol_dev, ldev)

static ssize_t lol_show_ver(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct ldd_dev *ld = to_ldd_dev(dev);
	struct lol_dev *kd = to_lol_dev(ld);
	return snprintf(buf, PAGE_SIZE, "%s\n", kd->msg);
}
static DEVICE_ATTR(ver, S_IRUGO, lol_show_ver, NULL);

static struct lol_dev lol;

static int register_lol_dev(struct lol_dev *lole)
{
	int err = 0;

	lole->ldev.name = name;
	lole->msg = v;
	err = register_ldd_dev(&lole->ldev);
	if (err)
		return err;

	if (device_create_file(&lole->ldev.dev, &dev_attr_ver))
		pr_info(KEKM SNL, "failed create lol device version file");

	return 0;
}

static int __init lol_init(void)
{
	pr_info(KEKM SNL, "init");
	return register_lol_dev(&lol);
}

static void __exit lol_exit(void)
{
	pr_info(KEKM SNL, "exit");
	device_unregister(&lol.ldev.dev);
}

module_init(lol_init);
module_exit(lol_exit);

MODULE_AUTHOR("ogokto");
MODULE_DESCRIPTION("lol device for the lddbus");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");
