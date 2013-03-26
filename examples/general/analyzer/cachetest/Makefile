# Copyright 02/12/07 Sun Microsystems, Inc. All Rights Reserved
#
# @(#)Makefile 1.13 07/02/12 SMI

FC     = f95
CC     = cc

# The API routines are inactive unless collection is actually performed.
# (The "include 'libfcollector.h'" in main.f90 isn't always necessary when
# compiling, however, if specified, then it must be locatable.)

# When the Analyzer package is installed with the compilers, its Fortran API
# libfcollector.h and libfcollector.a are automagically found by the compilers
# from the /opt/SUNWspro installation tree (as is the case for the C version).
# If other compilers are used, the paths need to be specified explicitly.     

# Root of tree where libfcollector and its API are installed
#S1SCCDIR = /opt/SUNWspro
#V8LIBDIR = -L$(S1SCCDIR)/lib
#V9LIBDIR = -L$(S1SCCDIR)/lib/v9

#ARCH = -m32
#ARCH = -m64

OPTS = -g $(ARCH) $(INCDIR)

LIBS = $(V8LIBDIR) $(V9LIBDIR) -lfcollector

TARGET    = cachetest

OBJ    = main.o dgemv_g.o dgemv_opt.o dgemv_hi.o dgemv_p.o barrier.o

TIMERS = wtime.o

default all: $(TARGET)
	@echo " ----DONE: $@ -----"

$(TARGET): $(OBJ) $(TIMERS)
	$(FC) -V -autopar $(OPTS) -o $(TARGET) $(OBJ) $(TIMERS) $(LIBS)

main.o: main.f90
	$(FC) -V -c -fast $(OPTS) -xinline= main.f90

dgemv_g.o: dgemv_g.f90
	$(FC) -V -c -O0 $(OPTS) -xinline= dgemv_g.f90

dgemv_opt.o: dgemv_opt.f90
	$(FC) -V -c -O2 $(OPTS) -xinline= dgemv_opt.f90

dgemv_hi.o: dgemv_hi.f90
	$(FC) -V -c -fast $(OPTS) -xinline= dgemv_hi.f90

dgemv_p.o: dgemv_p.f90
	$(FC) -V -c -fast -autopar $(OPTS) -xinline= dgemv_p.f90

barrier.o: barrier.f
	$(FC) -V -c -fast -openmp $(OPTS) -xinline= barrier.f

wtime.o: wtime.c
	$(CC) -V -c $(OPTS) wtime.c

run:
	time ./$(TARGET)

collect: $(TARGET)
	collect -o flops.er -S off -p on -h fpadd,on,fpmul,on $(TARGET)
	collect -o cpi.er -S off -p on -h cycles,on,insts,on $(TARGET)
	collect -o dcstall.er -S off -h dcstall,on $(TARGET)

demo: $(TARGET)
	collect -o test.clock.1.er -S off -p on $(TARGET)
	collect -o test.cpi.1.er -S off -p on -h cycles,on,insts,on $(TARGET)
	collect -o test.flops.1.er -S off -p on -h fpadd,on,fpmul,on $(TARGET)
	collect -o test.memory.1.er -S off -p on -h ecstall,on,cycles,on -g memory.erg $(TARGET)
	collect -o test.memory.2.er -S off -h icstall,on,dcstall,on -g memory.erg $(TARGET)

clobber: clean
	-rm -f $(TARGET)
	-er_rm -f *.er
	-rm -f *.out *.acct
	-rm -f *.erg
	-rm -f hs_err_pid*log

clean:
	-rm -f *.o
	-rm -f core*
