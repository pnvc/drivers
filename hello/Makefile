KO_FILE = hello.ko
KO_FILE2 = call_prinfo.ko
ifneq ($(KERNELRELEASE),)
	obj-m := hello.o
	#obj-m += call_prinfo.o
	hello-objs := hello_main.o hello_funcs.o

else
	PWD := $(shell pwd)
	KERNDIR ?= /lib/modules/$(shell uname -r)/build

default:
	$(MAKE) -C $(KERNDIR) M=$(PWD) modules

endif

clean:
	$(MAKE) -C $(KERNDIR) M=$(PWD) clean

ins:
	insmod $(KO_FILE)
	#insmod $(KO_FILE2)

rem:
	#rmmod $(KO_FILE2)
	rmmod $(KO_FILE)
