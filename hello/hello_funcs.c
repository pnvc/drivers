#include <linux/module.h>
#include <linux/sched.h>
#include <linux/version.h>
#include "hello_funcs.h"

void prinfo(const char *str)
{
	printk(KERN_ALERT "%s\n", str);
	printk(KERN_ALERT "Hello, World!:)\n");
	printk(KERN_ALERT "The proc: %s, the pid: %d\n",
		current->comm, current->pid);
	printk(KERN_ALERT "%X\n",
		LINUX_VERSION_CODE);
}

EXPORT_SYMBOL(prinfo);
