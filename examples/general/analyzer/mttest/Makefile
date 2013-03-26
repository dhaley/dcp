# Copyright 02/12/07 Sun Microsystems, Inc. All Rights Reserved
#
# @(#)Makefile 1.24 07/02/12 SMI

###############################################################################
# This Makefile builds the mttest demo code for the Sun Studio Performance Analyzer
#	It must be edited to select various options: the thread model, OS, compiler, etc.
#	The last option in each group is the one that obtains

# Select a thread interface, and comment the other one
	THREADS = SOLARIS
	THREADS = POSIX

# Select a thread flag, BOUND or UNBOUND, and comment the other one
	FLAG = UNBOUND
	FLAG = BOUND

# Select the OS type, and comment out the other one
	OSTYPE = Linux
	OSTYPE = Solaris

# Select a Compiler type, and comment out the other one
	CCTYPE = GNU
	CCTYPE = DEFAULT

# Select an architecture (32/64 bit), for the compiler type chosen, and comment out the others
	WSIZE = 32
	WSIZE = 64

# Select compile options, for the compiler type chosen, and comment out the others
	OFLAGS-DEFAULT = -g -xF -O
	OFLAGS-DEFAULT = -g -xF -fast
	OFLAGS-DEFAULT = -g -xF -xhwcprof -xdebugformat=dwarf -xO2
	OFLAGS-DEFAULT = -g -xF -xbinopt=prepare -xdebugformat=dwarf -xO2
	OFLAGS-DEFAULT = -g -xF

	OFLAGS-GNU 	= -g -O -Wall
	OFLAGS-GNU      = -g -Wall

# End of user selections
###############################################################################

ARCH            = -m${WSIZE}

CC-DEFAULT      = cc
CC-GNU          = gcc
CC              = ${CC-${CCTYPE}}

LIBS_SOLARIS-Solaris-DEFAULT 	= -mt $(LD_OPTS) -ldl
LIBS_POSIX-Solaris-DEFAULT 	= -mt $(LD_OPTS) -lposix4 -ldl
LIBS_POSIX-Linux-DEFAULT 	= $(LD_OPTS) -ldl

LIBS_SOLARIS-Solaris-GNU 	= -lpthread $(LD_OPTS) -ldl 
LIBS_POSIX-Solaris-GNU 		= -lpthread $(LD_OPTS) -lposix4 -ldl
LIBS_POSIX-Linux-GNU 		= -lpthread $(LD_OPTS) -ldl

LIBS 			= $(LIBS_$(THREADS)-$(OSTYPE)-$(CCTYPE))

OFLAGS          = ${OFLAGS-${CCTYPE}}

OPTS = $(OFLAGS) $(ARCH)

TARGETS= mttest

SRCS=	gethrtime.c \
	mttest.c \
	cksigmask.c \
	$(NULL)

OBJS=	gethrtime.o \
	mttest.o \
	cksigmask.o \
	$(NULL)

default all: $(TARGETS)
	@echo " ----DONE: $@ -----"

mttest: $(SRCS)
	-$(CC) $(OPTS) -o $@ -D$(THREADS) -D$(FLAG) $(SRCS) $(LIBS)

collect: $(TARGETS)
	collect -s on -o mttest.4.er mttest
	collect -s on -o mttest.1.er mttest -u

clobber: clean
	-rm -f $(TARGETS)
	-er_rm -f *.er
	-rm -f *.out *.acct

clean:
	-rm -f *.o *.s
	-rm -f core* hs_err_pid*.log

