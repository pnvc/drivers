#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>

#include "lddbus.h"

#define LDDBUS "lddbus"
#define LDDBUSM "lddbus: "
#define SNL "%s\n"

#define BUSVER "0.0.0.1"

// BUS
static int ldd_match(struct device *dev, struct device_driver *drv)
{
	if ((!strncmp(dev_name(dev), "kek", 3) && !strncmp(drv->name, "kek_drv", 7)) ||
		(!strncmp(dev_name(dev), "lol", 3) && !strncmp(drv->name, "lol_drv", 7)))
		return 1;
	return 0;
}

static int ldd_uevent(const struct device *dev, struct kobj_uevent_env *env)
{
	if (add_uevent_var(env, "LDDBUS_VERSION=%s", BUSVER))
		return -ENOMEM;
	return 1;
}

static ssize_t version_show(const struct bus_type *bus, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s\n", BUSVER);
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

// DEVICES
static void ldd_dev_release(struct device *dev)
{
	pr_info(LDDBUSM SNL, "ldd device released");
}

int register_ldd_dev(struct ldd_dev *ldddev)
{
	ldddev->dev.bus = &ldd_bus_type;
	ldddev->dev.parent = &ldd_bus;
	ldddev->dev.release = ldd_dev_release;
	ldddev->dev.init_name = ldddev->name;
	return device_register(&ldddev->dev);
}
EXPORT_SYMBOL(register_ldd_dev);

static ssize_t show_version(struct device_driver *drv, char *buf)
{
	struct ldd_drv *ldrv = to_ldd_drv(drv);
	return snprintf(buf, PAGE_SIZE, "%s\n", ldrv->ver);
}

// DRIVERS
int register_ldd_drv(struct ldd_drv *drv)
{
	int ret;

	drv->drv.bus = &ldd_bus_type;
	ret = driver_register(&drv->drv);
	if (ret)
		return ret;

	drv->ver_attr.attr.name = "version";
	drv->ver_attr.attr.mode = S_IRUGO;
	drv->ver_attr.show = show_version;
	drv->ver_attr.store = NULL;
	return driver_create_file(&drv->drv, &drv->ver_attr);
}
EXPORT_SYMBOL(register_ldd_drv);

// CLASS
static const char *class_ver = "0.0.0.97";

static void ldd_class_release(const struct class *class)
{
	pr_info(LDDBUSM SNL, "ldd class released");
}

static ssize_t ver_show(const struct class *class, const struct class_attribute *attr, char *buf)
{
	return snprintf(buf, PAGE_SIZE, "%s\n", class_ver);
}
static CLASS_ATTR_RO(ver); // struct class_attribute class_attr_ver
static struct attribute *ldd_attrs[] = {
	&class_attr_ver.attr,
	NULL
};
ATTRIBUTE_GROUPS(ldd); // struct attribute_group *ldd_groups[]

struct class ldd_class = {
	.name = "ldd_class",
	.class_release = ldd_class_release,
	.class_groups = ldd_groups,
};

static int __init lddbus_init(void)
{
	int ret;
	int ret_bus_create_file;

	ret = bus_register(&ldd_bus_type);
	if (ret)
		return ret;

	ret_bus_create_file = bus_create_file(&ldd_bus_type, &bus_attr_version);
	if (ret_bus_create_file)
		pr_info(LDDBUSM SNL, "Unable create bus file version");

	ret = device_register(&ldd_bus);
	if (ret) {
		if (!ret_bus_create_file)
			bus_remove_file(&ldd_bus_type, &bus_attr_version);
		bus_unregister(&ldd_bus_type);
		return ret;
	}

	ret = class_register(&ldd_class);
	if (ret) {
		device_unregister(&ldd_bus);
		if (!ret_bus_create_file)
			bus_remove_file(&ldd_bus_type, &bus_attr_version);
		bus_unregister(&ldd_bus_type);
		return ret;
	}

	pr_info(LDDBUSM SNL, "started");
	return 0;
}

static void __exit lddbus_exit(void)
{
	device_unregister(&ldd_bus);
	bus_remove_file(&ldd_bus_type, &bus_attr_version); // rem bus file
	bus_unregister(&ldd_bus_type); // rem bus

	class_unregister(&ldd_class);

	pr_info(LDDBUSM SNL, "exited");
}

module_init(lddbus_init);
module_exit(lddbus_exit);

MODULE_AUTHOR("ogokto");
MODULE_DESCRIPTION("ldd bus as example");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");
