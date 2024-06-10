KO_FILE = lpci.ko

ifneq ($(KERNELRELEASE),)
	obj-m := lpci.o
else
	PWD = $(shell pwd)
	KERNDIR = /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules
endif

clean:
	$(MAKE) -C $(KERNDIR) M=$(PWD) clean

in:
	@insmod $(KO_FILE)

rm:
	@rmmod $(KO_FILE)

inm:
	@insmod $(KO_FILE) use_mem=1
