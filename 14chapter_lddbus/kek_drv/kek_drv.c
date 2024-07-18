#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>

#include "../lddbus.h"

#define KEKDRV "kekdrv"
#define KEKDRVM "kekdrv: "
#define SNL "%s\n"

static const char v[] = "0.0.1.34";
static char name[] = "kek_drv";

static struct ldd_drv kek_drv = {
	.ver = v,
	.drv = {
		.name = name
	}
};

static int __init kek_drv_init(void)
{
	pr_info(KEKDRVM SNL, "init");
	return register_ldd_drv(&kek_drv);
}

static void __exit kek_drv_exit(void)
{
	pr_info(KEKDRVM SNL, "exit");
	driver_unregister(&kek_drv.drv);
}

module_init(kek_drv_init);
module_exit(kek_drv_exit);

MODULE_AUTHOR("ogokto");
MODULE_DESCRIPTION("kek driver for the kek device");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");
