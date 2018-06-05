# If KERNELRELEASE is defined, we've been invoked from the
# kernel build system and can use its language.
ifneq ($(KERNELRELEASE),)
	obj-m := nf.o
# Otherwise we were called directly from the command
# line; invoke the kernel build system.
else
	#KERNELDIR ?= /lib/modules/$(shell uname -r)/build
	KERNELDIR ?= /home/safouane/workspace/linux/
	PWD := $(shell pwd)
default:
	CFLGAS="-std=c99" $(MAKE) -C $(KERNELDIR) M=$(PWD) modules
endif
clean:
	rm -rf -- *mod.c *.o *er* *.ko .[!.]*
