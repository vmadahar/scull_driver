PWD := $(shell pwd)
KERNELDIR ?= $(PWD)/linux

obj-m := scull_driver.o
scull_driver-objs := scull.o

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	
clean:
	rm -rf *.o *~* modules.order Module.symvers  scull_driver.ko  scull_driver.mod.c

