#include <linux/module.h>
#include <linux/init.h>

static int __init mnwdev_init(void)
{

	pr_info("mnwdev: inited\n");
	return 0;
}

static void __exit mnwdev_exit(void)
{
	pr_info("mnwdev: exited\n");
}

module_init(mnwdev_init);
module_exit(mnwdev_exit);

MODULE_AUTHOR("nix4n");
MODULE_DESCRIPTION("my network device try");
MODULE_VERSION("0.0.0.1");
MODULE_LICENSE("GPL");
