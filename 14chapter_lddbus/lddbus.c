#include <linux/module.h>
#include <linux/init.h>

#include <linux/device.h>

#define LDDBUS "lddbus"
#define LDDBUSM "lddbus: "
#define SNL "%s\n"

static char *Version = "Revision: 1.9";

// BUS
static int ldd_match(struct device *dev, struct device_driver *drv)
{
	return !strncmp(dev_name(dev), drv->name, strlen(drv->name));
}

static int ldd_uevent(const struct device *dev, struct kobj_uevent_env *env)
{
	if (add_uevent_var(env, "LDDBUS_VERSION=%s", Version))
		return -ENOMEM;
	return 1;
}

static ssize_t version_show(const struct bus_type *bus, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s\n", Version);
}
static BUS_ATTR_RO(version); // bus_attr_version

static struct bus_type ldd_bus_type = {
	.name = "ldd",
	.match = ldd_match,
	.uevent = ldd_uevent
};

// BUS DEVICE
static void ldd_bus_release(struct device *dev)
{
	pr_info(LDDBUSM SNL, "ldd_bus device released");
}

static struct device ldd_bus = {
	.release = ldd_bus_release,
	.init_name = "ldd",
};

// DEVICE
static char ldd_dev_name[] = "dev1";
struct ldd_dev {
	char *name;
	struct ldd_drv *drv;
	struct device dev;
};
#define to_ldd_dev(dev) container_of(dev, struct ldd_dev, dev);

static struct ldd_dev dev1 = {
	.name = ldd_dev_name
};

static void ldd_dev_release(struct device *dev)
{
	pr_info(LDDBUSM SNL, "dev1 released");
}

int register_ldd_dev(struct ldd_dev *ldddev)
{
	ldddev->dev.bus = &ldd_bus_type;
	ldddev->dev.parent = &ldd_bus;
	ldddev->dev.release = ldd_dev_release;
	ldddev->dev.init_name = ldddev->name;
	ldddev->dev.driver_data = &dev1;
	return device_register(&ldddev->dev);
}
EXPORT_SYMBOL(register_ldd_dev);

static ssize_t dev1_show(struct device *dev, struct device_attribute *attr,
		char *buf)
{
	struct ldd_dev *d = to_ldd_dev(dev);
	return snprintf(buf, PAGE_SIZE, "%s\n", d->name);
}
static DEVICE_ATTR(name, S_IRUGO, dev1_show, NULL);


static int __init lddbus_init(void)
{
	int ret;

	ret = bus_register(&ldd_bus_type);
	if (ret)
		return ret;

	if (bus_create_file(&ldd_bus_type, &bus_attr_version))
		pr_info(LDDBUSM SNL, "Unable create bus file version");

	ret = device_register(&ldd_bus);
	if (ret)
		return ret;

	ret = register_ldd_dev(&dev1);
	if (ret)
		return ret;

	if (device_create_file(&dev1.dev, &dev_attr_name))
		pr_info(LDDBUSM SNL, "Unable create dev1 name file");

	pr_info(LDDBUSM SNL, "started");
	return 0;
}

static void __exit lddbus_exit(void)
{
	device_unregister(&dev1.dev);
	device_unregister(&ldd_bus);
	bus_remove_file(&ldd_bus_type, &bus_attr_version); // rem bus file
	bus_unregister(&ldd_bus_type); // rem bus

	pr_info(LDDBUSM SNL, "exited");
}

module_init(lddbus_init);
module_exit(lddbus_exit);

MODULE_AUTHOR("ogokto");
MODULE_DESCRIPTION("ldd bus as example");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");
