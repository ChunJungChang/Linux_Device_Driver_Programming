#http://www.cs.bham.ac.uk/~exr/lectures/opsys/14_15/examples/modules/

EXTRA_CFLAGS += -Wall
CFILES = kernelRead.c

obj-m += sample.o
sample-objs := $(CFILES:.c=.o)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
