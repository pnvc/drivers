MODULE_NAME = usb_vpd
VEND_PARAM = 0x0951
PROD_PARAM = 0x1666

KO_FILE = $(MODULE_NAME).ko

ifneq ($(KERNELRELEASE),)
	obj-m := $(MODULE_NAME).o
else
	PWD = $(shell pwd)
	KERNDIR = /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules modules_install
	@depmod
endif

clean:
	$(MAKE) -C $(KERNDIR) M=$(PWD) clean

inm:
	@modprobe $(MODULE_NAME) vend=$(VEND_PARAM) prod=$(PROD_PARAM)

rmm:
	@rmmod $(MODULE_NAME)
