#include <linux/module.h>
#include <linux/init.h>

#define MM151 "mm151"
#define MM151M "mm151: "

static int __init mm151_init(void)
{
	return 0;
}

static void __exit mm151_exit(void)
{
	;
}

module_init(mm151_init);
module_exit(mm151_exit);

MODULE_AUTHOR("nx4n");
MODULE_DESCRIPTION("mem manag 15.1");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");