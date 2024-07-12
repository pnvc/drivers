#include <linux/module.h>
#include <linux/init.h>

#include <linux/device.h>

struct bus_type lddbus_type = {
	.name = "lddbus",
	.match = lddbus_match,
	.hotplug = lddbus_hotplug
};

static int __init lddbus_init(void)
{
	return 0;
}

static void __exit lddbus_exit(void)
{
	return;
}

module_init(lddbus_init);
module_exit(lddbus_exit);

MODULE_AUTHOR("ogokto");
MODULE_DESCRIPTION("ldd bus aas example");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");
