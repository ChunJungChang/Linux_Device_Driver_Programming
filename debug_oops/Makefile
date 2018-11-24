obj-m := oops.o
KDIR  := /lib/modules/$(shell uname -r)/build
PWD   := $(shell pwd)
SYM    = $(PWD)

MY_CFLAGS += -g -DDEBUG
ccflags-y += ${MY_CFLAGS}
CC += ${MY_CFLAGS}
 
all:
	make -C $(KDIR) M=$(PWD) modules

debug:
	make -C $(KDIR) M=$(PWD) modules
	EXTRA_CFLAGS="$(MY_CFLAGS)"

clean:
	make -C $(KDIR) M=$(PWD) clean
