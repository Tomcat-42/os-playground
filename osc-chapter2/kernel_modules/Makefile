# https://www.kernel.org/doc/Documentation/kbuild/modules.txt
obj-m += adriana.o simple.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(shell pwd) clean
