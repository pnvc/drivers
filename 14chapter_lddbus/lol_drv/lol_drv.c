#include <linux/module.h>
#include <linux/init.h>
#include <linux/device.h>

#include "../lddbus.h"

#define LOLDRV "loldrv"
#define LOLDRVM "loldrv: "
#define SNL "%s\n"

static const char v[] = "0.0.1.34";
static char name[] = "lol_drv";

static struct ldd_drv lol_drv = {
	.ver = v,
	.drv = {
		.name = name
	}
};

static int __init lol_drv_init(void)
{
	pr_info(LOLDRVM SNL, "init");
	return register_ldd_drv(&lol_drv);
}

static void __exit lol_drv_exit(void)
{
	pr_info(LOLDRVM SNL, "exit");
	driver_unregister(&lol_drv.drv);
}

module_init(lol_drv_init);
module_exit(lol_drv_exit);

MODULE_AUTHOR("ogokto");
MODULE_DESCRIPTION("lol driver for the lol device");
MODULE_LICENSE("GPL");
MODULE_VERSION("0.0.0.1");
