PWD		:= $(shell pwd)
KVERSION	:= $(shell uname -r)

CFILES		:= main.c sub.c

obj-m		:= hello.o

hello-objs	:= $(CFILES:.c=.o)

all:
	make -C /usr/src/linux-headers-$(KVERSION) M=$(PWD) V=1 modules

clean:
	make -C /usr/src/linux-headers-$(KVERSION) M=$(PWD) V=1 clean
