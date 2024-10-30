#!/bin/bash
if [ -z "$1" ]; then
	echo 1 enter module name
	exit 1
fi
if [ -z "$2" ]; then
	echo 2 enter module desc
	exit 1
fi
if [ -z "$3" ]; then
	echo 3 enter module ver
	exit 1
fi

FILE="$1".c
UPPER_NAME=`echo "$1" | tr a-z A-Z`
NAME="$1"
DESC="${@: 2:(($# - 2))}"
VER="${@: -1}"

# Makfile
printf "MODULE_NAME = "$NAME"

ifneq (\$(KERNELRELEASE),)
	obj-m = \$(MODULE_NAME).o
else
	PWD = \$(shell pwd)
	KERNDIR = /lib/modules/\$(shell uname -r)/build/
default:
	\$(MAKE) -C \$(KERNDIR) M=\$(PWD) modules modules_install
	@depmod
endif

clean:
	\$(MAKE) -C \$(KERNDIR) M=\$(PWD) clean

in:
	@modprobe \$(MODULE_NAME)

rm:
	@rmmod \$(MODULE_NAME)" > Makefile

# dmesg script
echo "dmesg | grep "$NAME" | tail -15" > dmesg
chmod +x dmesg

# NAME.c file
printf "#include <linux/module.h>
#include <linux/init.h>

static int __init "$NAME"_init(void)
{
	pr_info(\""$NAME": inited\\\n\");
	return 0;
}

static void __exit "$NAME"_exit(void)
{
	pr_info(\""$NAME": exited\\\n\");
}

module_init("$NAME"_init);
module_exit("$NAME"_exit);

MODULE_AUTHOR(\"nx4n\");
MODULE_DESCRIPTION(\"${DESC}\");
MODULE_VERSION(\""$VER"\");
MODULE_LICENSE(\"GPL\");" > $FILE
