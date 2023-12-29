SCULL_DEBUG = y

ifeq ($(SCULL_DEBUG),y)
	SCULL_DFLAGS = -O -g -DSCULL_DEBUG
else
	SCULL_DFLAGS = -O2
endif

ccflags-y := $(SCULL_DFLAGS)

KO_FILE = scull.ko

ifneq ($(KERNELRELEASE),)
	obj-m := scull.o
	scull-objs := scull_main.o

else
	PWD := $(shell pwd)
	KERNDIR ?= /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules

endif

clean:
	$(MAKE) -C $(KERNDIR) M=$(PWD) clean

ins:
	@insmod $(KO_FILE)

rem:
	@rmmod $(KO_FILE)
