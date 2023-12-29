#include <linux/init.h>
#include <linux/module.h>
#include <linux/moduleparam.h>
#include "hello_funcs.h"

static char *str = "str";
static int howmany = 1;
static int arr[10];
static unsigned int params_supplied;

module_param(str, charp, 0); // no one see
module_param(howmany, int, S_IRUGO); // see but cant change
module_param_array(arr, int, &params_supplied, S_IRUGO|S_IWUSR); // see and change

static int hello_init(void)
{
	for (int i = 0; i < 10; i++) {
		printk(KERN_ALERT "%d, %u\n", arr[i], params_supplied);
	}
	for (int i = 0; i < howmany; i++)
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
MODULE_DESCRIPTION("Just prinfo function");
MODULE_VERSION("0.0.1");
