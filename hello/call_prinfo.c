#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>

extern void prinfo(const char *str);

static int hello_init(void)
{
	char *str = "qwerty";
	prinfo(str);
	return 0;
}

static void hello_exit(void)
{
	printk(KERN_ALERT "Goodbye, World!:)\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Me :)");
MODULE_DESCRIPTION("Call prinfo function from the hello module");
MODULE_VERSION("0.0.1");
