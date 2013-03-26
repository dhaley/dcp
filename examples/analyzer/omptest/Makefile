# Copyright 01/10/07 Sun Microsystems, Inc. All Rights Reserved
#
# @(#)Makefile 1.11 07/01/10 SMI

CC	= cc
LLDLIBS = $(LD_OPTS) -lc

ARCH = -xarch=native 
#ARCH = -xarch=v7
#ARCH = -xarch=v8
#ARCH = -xarch=v9

#OFLAGS = -g -V -v
#OFLAGS = -g -fast -V -v
#OFLAGS = -g -O -V -v
OFLAGS = -g -O3 -mp=openmp -explicitpar -depend -stackvar -loopinfo -V -v
#OFLAGS = -g -fast -mp=openmp -explicitpar -depend -stackvar -loopinfo -V -v

OPTS = $(OFLAGS) $(ARCH)
SOPTS = $(OFLAGS) -fixed -mp=sun -parallel -xreduction $(ARCH)
YOPTS = $(OFLAGS) -fixed -mp=cray -parallel -xreduction $(ARCH)

TARGETS= omptest

HDRS=   defs.h
SRCS=  \
	omptest.f \
	bardo.f \
	dyndo.f \
	pdo.f \
	pardo.f \
	psec.f \
	parsec.f \
	atomsum.f \
	critsum.f \
	redsum.f \
	timing.c \
	gethrtime.c \
	$(NULL)

SSRCS= \
	autodo.f90 \
	autosum.f90 \
	expldo.f90 \
	explsum.f90 \
	serialdo.f90 \
	serialsum.f90 \
	$(NULL)

YSRCS= \
	craydo.F \
	craysum.F \
	$(NULL)

OBJECTS= \
	omptest.o \
	craydo.o \
	craysum.o \
	bardo.o \
	dyndo.o \
	serialdo.o \
	serialsum.o \
	autodo.o \
	autosum.o \
	expldo.o \
	explsum.o \
	pdo.o \
	pardo.o \
	psec.o \
	parsec.o \
	atomsum.o \
	critsum.o \
	redsum.o \
	timing.o \
	gethrtime.o \
	$(NULL)

default all: $(TARGETS)
	@echo " ----DONE: $@ -----"

omptest: $(OBJECTS)
	@echo " ---- $@ -----"
	f90 $(OPTS) -o omptest $(OBJECTS)

.f90.o:
	f90 $(SOPTS) -c $<  1> $<.make.out 2>&1

.f.o:
	f90 $(OPTS) -c $< 1> $<.make.out 2>&1

.F.o:
	f90 $(YOPTS) -c $< 1> $<.make.out 2>&1

%.o : %.c $(HDRS)
	@echo " ---- $@ -----"
	$(CC) $(ARCH) -g -c `basename $@ .o`.c

expt:
	dbx omptest < omptest.debug.in 1> run.out 2>&1

list: test.1.er
	for k in $(SRCS) $(SSRCS) $(YSRCS) ; \
		do \
			echo "doing $$k" ; \
			er_print -out $$k.src -src $$k 1 test.1.er ; \
			er_print -out $$k.dis -dis $$k 1 test.1.er ; \
		done

collect: omptest
	csh ./example_script

clobber: clean
	-rm -f $(TARGETS)
	-rm -f *.mod
	-rm -f *.make.out
	-rm -f *.src
	-rm -f *.dis
	-er_rm -f *.er
	-rm -rf omptest.acct
	-rm -rf run.out

clean:
	-rm -f *.o
	-rm -f core*
	-rm -f hs_err*.log
