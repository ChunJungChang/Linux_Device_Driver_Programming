#http://tuxthink.blogspot.tw/2013/10/creation-of-proc-entrt-using.html

EXTRA_CFLAGS += -Wall
CFILES = proc_read_data.c

obj-m += sample.o
sample-objs := $(CFILES:.c=.o)

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
