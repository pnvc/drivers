MODULE_NAME = xarr

ifneq ($(KERNELRELEASE),)
	obj-m = $(MODULE_NAME).o
else
	PWD = $(shell pwd)
	KERNDIR = /lib/modules/$(shell uname -r)/build/
default:
	$(MAKE) -C $(KERNDIR) M=$(PWD)
endif

clean:
	$(MAKE) -C $(KERNDIR) M=$(PWD) clean

in:
	@insmod $(MODULE_NAME).ko

rm:
	@rmmod $(MODULE_NAME).ko
