# Copyright 2002 Sun Microsystems, Inc. All Rights Reserved
#
# Makefile for memtest and gc_memtest
#

OBJS = memtest.o init_array.o init_array_loc.o  \
       print_list.o free_list.o bld_cust_list.o

CCFLAGS = -c -g -DSTRDUP

LDFLAGS = -g

#gc_memtest : $(OBJS)
#	 CC -o gc_memtest -lgc_dbg -g $(OBJS)

memtest : $(OBJS)
	 cc $(LDFLAGS) $(OBJS) -o memtest

memtest.o : memtest.c
	 cc $(CCFLAGS) memtest.c

init_array.o : init_array.c
	 cc $(CCFLAGS) init_array.c

init_array_loc.o : init_array_loc.c
	 cc $(CCFLAGS) init_array_loc.c

print_list.o : print_list.c
	 cc $(CCFLAGS) print_list.c

free_list.o : free_list.c
	 cc $(CCFLAGS) free_list.c

bld_cust_list.o : bld_cust_list.c
	 cc $(CCFLAGS) bld_cust_list.c

clean :
	@rm -rf *.o memtest gc_memtest core gc.log *.er .*.er

reset:
	 cp memtest.c.save memtest.c
	 cp init_array.c.save init_array.c
