MODULE_NAME = dir012
KO_FILE = dir012.ko

ifneq ($(KERNELRELEASE),)
	obj-m := dir012.o
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
	@modprobe $(MODULE_NAME) || insmod $(KO_FILE)

rmm:
	@rmmod $(MODULE_NAME)
