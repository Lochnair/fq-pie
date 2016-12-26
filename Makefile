KDIR := /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
VERBOSE = 0
obj-m := fq_pie.o pie.o
fq_pie-objs := sch_fq_pie.o
pie-objs := sch_pie.o

#ccflag-y := -O0 -g -Wall
ccflag-y := -O2

all:
	$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules

clean:
	rm -f *.o
	rm -f *.ko
	rm -f .*.cmd
	rm -f *.mod.c
	rm -f *~
	rm -f modules.order
	rm -f Module.markers
	rm -f Module.symvers
	rm -rf .tmp_versions
