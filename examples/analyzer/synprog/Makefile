# Copyright 02/12/07 Sun Microsystems, Inc. All Rights Reserved
#
# @(#)Makefile 1.33 07/02/12 SMI

###############################################################################
# This Makefile builds the synprog demo code for the Sun Studio Performance Analyzer
#	It must be edited to select various options: OS, compiler, etc.
#       The last option in each group is the one that obtains

# Select the OS type, and comment out the other one
	OSTYPE = Linux
	OSTYPE  = Solaris

# Select a Compiler type, and comment out the other one
	CCTYPE = GNU
	CCTYPE = DEFAULT

# Select an architecture (32/64 bit), for the compiler type chosen, and comment out the others
	WSIZE = 32
	WSIZE = 64

# Select compile options, for the compiler type chosen, and comment out the others
	OFLAGS-DEFAULT  = -g -xF -O
	OFLAGS-DEFAULT  = -g -xF -fast
	OFLAGS-DEFAULT 	= -g -xF -xhwcprof -xdebugformat=dwarf -xO2
	OFLAGS-DEFAULT 	= -g -xF -xbinopt=prepare -xdebugformat=dwarf -xO2
	OFLAGS-DEFAULT 	= -g -xF

	OFLAGS-GNU 	= -g -O -Wall
	OFLAGS-GNU      = -g -Wall

# End of user selections
###############################################################################
# Note, to check HW counter profiling, use the #OPTS that has
#	-DHWC, and the #LLDLIBS that has -lcpc.  Only cksigmask.c cares.
#	This will only work on Solaris 8 and above....


CC-DEFAULT	= cc
CC-GNU		= gcc
CC		= ${CC-${CCTYPE}}

SHAREDOPT-DEFAULT	= -Kpic
SHAREDOPT-GNU		= -fpic
SHAREDOPT		= ${SHAREDOPT-${CCTYPE}}

SHAREDLIBOPTS-Solaris           =
SHAREDLIBOPTS-Linux             = -rdynamic
SHAREDLIBOPTS           = $(SHAREDLIBOPTS-$(OSTYPE))

ARCH            = -m${WSIZE}
OFLAGS		= ${OFLAGS-${CCTYPE}}

OPTS 		= $(OFLAGS) $(ARCH)
#OPTS 		= $(OFLAGS) $(ARCH) -DHWC

LD_FLAGS-DEFAULT	= -G ${ARCH}
LD_FLAGS-GNU	= -shared ${ARCH}
LD_FLAGS	= ${LD_FLAGS-${CCTYPE}}

LLDLIBS 	= $(LD_OPTS) -ldl -lc
#LLDLIBS 	= $(LD_OPTS) -ldl -lc -lcpc

TARGETS= synprog so_syn.so so_syx.so

SRCS= \
	gethrtime.c \
	synprog.c \
	callso.c \
	callsx.c \
	endcases.c \
	fitos.c \
	iosyn.c \
	pagethrash.c \
	stopwatch.c \
	cksigmask.c \
	$(NULL)

OBJS= \
	gethrtime.o \
	synprog.o \
	callso.o \
	callsx.o \
	endcases.o \
	fitos.o \
	iosyn.o \
	pagethrash.o \
	stopwatch.o \
	cksigmask.o \
	$(NULL)

HDRS= \
	inc_body.h \
	inc_brace.h \
	inc_func.h \
	inc_inline.h \
	inc_macro.h \
	stopwatch.h \
	$(NULL)


default all: $(TARGETS)
	@echo " ----DONE: $@ -----"

synprog: $(SRCS) $(HDRS)
	-$(CC) $(OPTS) $(SHAREDLIBOPTS) -o synprog $(SRCS) $(LLDLIBS)

so_syx.o: so_syx.c
	-$(CC) $(OPTS) $(SHAREDOPT) -c so_syx.c

so_syx.so: so_syx.o
	-$(CC) $(LD_FLAGS) $(LD_OPTS) -o $@ so_syx.o -lc

so_syn.o: so_syn.c
	-$(CC) $(OPTS) $(SHAREDOPT) -c so_syn.c

so_syn.so: so_syn.o
	-$(CC) $(LD_FLAGS) $(LD_OPTS) -o $@ so_syn.o -lc

collect: $(TARGETS)
	collect synprog

clobber: clean
	-rm -f $(TARGETS)
	-er_rm -f *.er
	-rm -rf synprog.acct* synprog.instr*
	-rm -rf synprog.acct*

clean:
	-rm -f *.o
	-rm -f core*
	-rm -f hs_err_pid*log
	-rm -f ipc_log
