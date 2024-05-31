MODULE_NAME = led_control
 
obj-m += $(MODULE_NAME).o
 
all:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

install:
	sudo insmod $(MODULE_NAME).ko

uninstall:
	sudo rmmod $(MODULE_NAME)

clean:
	$(MAKE) -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean

.PHONY: all install uninstall clean
