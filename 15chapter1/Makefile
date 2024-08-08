MODULE_NAME = mm151

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

rm:
	@rmmod $(MODULE_NAME)