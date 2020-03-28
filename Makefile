# CONFIG_MODULE_SIG=n 
# CONFIG_MODULE_SIG_ALL=n

driver_name:=dev_meng

DIST ?= $(shell uname -r)
KDIR:=/lib/modules/$(DIST)/build/
PWD:=$(shell pwd)

obj-m := $(driver_name).o
$(driver_name)-objs += my_drv.o

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf *.ko *.o .*.cmd *.symvers *.mod* *.order

