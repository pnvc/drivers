MODULE_NAME = lddbus
KO_FILE = lddbus.ko

ifneq ($(KERNELRELEASE),)
	obj-m := lddbus.o
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
