KO_FILE = scullpipe.ko

ifneq ($(KERNELRELEASE),)
	obj-m := scullpipe.o
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
