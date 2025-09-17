obj-m += p2p.o
PWD := $(CURDIR)

# There are two gcc installed in this pc so adding the cc path; generally not required

all:
	$(MAKE) CC=/opt/gcc83/bin/gcc -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	$(MAKE) CC=/opt/gcc83/bin/gcc -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean