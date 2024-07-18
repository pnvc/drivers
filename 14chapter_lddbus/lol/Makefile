KBUILD_EXTRA_SYMBOLS=/root/drivers/14chapter_lddbus/Module.symvers
MODULE_NAME = lol
KO_FILE = lol.ko

ifneq ($(KERNELRELEASE),)
	obj-m := lol.o
else
	PWD = $(shell pwd)
	KERNDIR = /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules modules_install
	@depmod
endif

clean:
	$(MAKE) -C $(KERNDIR) M=$(PWD) clean
	@./rmrfupdates

inm:
	@modprobe $(MODULE_NAME)

rmm:
	@rmmod $(MODULE_NAME)
