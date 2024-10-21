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
	if ((!strncmp(dev_name(dev), "kek", 3) &&
				!strncmp(drv->name, "kek_drv", 7)) ||
				(!strncmp(dev_name(dev), "lol", 3) &&
				 !strncmp(drv->name, "lol_drv", 7))) {
		pr_info(LDDBUSM "device: %s with driver: %s are added",
				dev_name(dev), drv->name);
		return 1;
	}
	return 0;
}

static int ldd_uevent(const struct device *dev, struct kobj_uevent_env *env)
{
	if (!strncmp(dev_name(dev), "kek", 3)) {
		pr_info(LDDBUSM SNL, "kek dev in UEVENT!");
		if (add_uevent_var(env, "KEK=kek"))
			return -ENOMEM;
	}
	if (add_uevent_var(env, "LDDBUS_VERSION=%s", BUSVER))
		return -ENOMEM;
	pr_info(LDDBUSM SNL, "UEVENT!");
	return 0;
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

// CLASS
static const char *class_ver = "0.0.0.97";

static void ldd_class_release(const struct class *class)
{
	pr_info(LDDBUSM SNL, "ldd class released");
}

static ssize_t ver_show(const struct class *class,
		const struct class_attribute *attr, char *buf)
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

int ldd_class_device_register(struct device *dev)
{
	dev->class = &ldd_class;
	dev->parent = &ldd_bus;
	return device_register(dev);
}
EXPORT_SYMBOL(ldd_class_device_register);

// CLASS INTERFACE
static int ldd_class_iface_add(struct device *dev)
{
	pr_info(LDDBUSM "%s " SNL, dev_name(dev), "added");
	return 0;
}
static void ldd_class_iface_remove(struct device *dev)
{
	pr_info(LDDBUSM "%s " SNL, dev_name(dev), "removed");
}
static struct class_interface ldd_class_iface = {
	.class = &ldd_class,
	.add_dev = ldd_class_iface_add,
	.remove_dev = ldd_class_iface_remove
};

// DEVICES
static void ldd_dev_release(struct device *dev)
{
	pr_info(LDDBUSM "%s " SNL, dev_name(dev), "device released");
}

struct class ldd_class;

int register_ldd_dev(struct ldd_dev *ldddev)
{
	ldddev->dev.bus = &ldd_bus_type;
	ldddev->dev.parent = &ldd_bus;
	ldddev->dev.release = ldd_dev_release;
	//ldddev->dev.class = &ldd_class;
	ldddev->dev.init_name = ldddev->name;
	pr_info(LDDBUSM"%s "SNL, ldddev->dev.init_name, "added");
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


static int __init lddbus_init(void)
{
	int ret;
	int ret_bus_create_file;

	ret = class_register(&ldd_class);
	if (ret)
		return ret;

	ret = class_interface_register(&ldd_class_iface);
	if (ret) {
		class_unregister(&ldd_class);
		return ret;
	}

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

	pr_info(LDDBUSM SNL, "started");
	return 0;
}

static void __exit lddbus_exit(void)
{
	device_unregister(&ldd_bus);
	bus_remove_file(&ldd_bus_type, &bus_attr_version); // rem bus file
	bus_unregister(&ldd_bus_type); // rem bus

	class_interface_unregister(&ldd_class_iface);
	class_unregister(&ldd_class);

	pr_info(LDDBUSM SNL, "exited");
}

module_init(lddbus_init);
module_exit(lddbus_exit);

MODULE_AUTHOR("ogokto");
MODULE_DESCRIPTION("ldd bus as example");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");
