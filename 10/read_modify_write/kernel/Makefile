ccflags-y += -S
ccflags-y += -Wall

CFILES = main.c

obj-m += sample.o
#
# Compiler main.c to assembly code, main.s.
# It will be failed, CH7-8 Page257.
#
sample-y := main.s

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
