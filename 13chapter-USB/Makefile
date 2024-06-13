KO_FILE = lusb.ko

ifneq ($(KERNELRELEASE),)
	obj-m := lusb.o
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

in:
	@insmod $(KO_FILE)

rm:
	@rmmod $(KO_FILE)

inm:
	@insmod $(KO_FILE) use_mem=1
