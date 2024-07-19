MODULE_NAME = 2tldm
KO_FILE = 2tldm.ko

ifneq ($(KERNELRELEASE),)
	obj-m := 2tldm.o
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
