ifneq ($(KERNELRELEASE),)
	obj-m := scull_driver.o
	scull_driver-objs := scull.o

else
	PWD := $(shell pwd)
	KERNELDIR ?= $(PWD)/linux


default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

endif
	
clean:
	rm -rf *.o *~* modules.order Module.symvers  scull_driver.ko  scull_driver.mod.c .scull* .tmp* scull_app

app:
	gcc scull_app.c -o scull_app
