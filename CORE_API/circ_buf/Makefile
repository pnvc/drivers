MODULE_NAME = cb

ifneq ($(KERNELRELEASE),)
	obj-m = $(MODULE_NAME).o
else
	PWD = $(shell pwd)
	KERNDIR = /lib/modules/$(shell uname -r)/build/
default:
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules modules_install
	@depmod
endif

clean:
	$(MAKE) -C $(KERNDIR) M=$(PWD) clean

in:
	@modprobe $(MODULE_NAME)
	@if ! [ -e "cb" ]; then mknod cb c 243 0; fi

rm:
	@rmmod $(MODULE_NAME)
