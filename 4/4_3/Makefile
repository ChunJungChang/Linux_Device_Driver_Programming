PWD		:= $(shell pwd)
KVERSION	:= $(shell uname -r)

obj-m		:= hello.o

all:
	make -C /usr/src/linux-headers-$(KVERSION) M=$(PWD) V=1 modules

clean:
	make -C /usr/src/linux-headers-$(KVERSION) M=$(PWD) V=1 clean
