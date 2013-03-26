# Copyright 04/17/07 Sun Microsystems, Inc. All Rights Reserved
# @(#)Makefile 1.1 07/04/17 SMI


###############################################################################
# This Makefile builds the prime demo code for the data race detection tool 
#	It must be edited to select various options: OS, compiler, etc.
#       The last option in each group is the one that obtains

# Select the OS type, and comment out the other one
	OSTYPE  = Solaris

# Select a Compiler type, and comment out the other one
	CCTYPE = DEFAULT

# Select an architecture (32/64 bit), for the compiler type chosen,
# and comment out the others
	WSIZE = 64
	WSIZE = 32

# End of user selections
###############################################################################

CC-DEFAULT = cc
COLLECT    = collect
ER_PRINT   = er_print
THA        = tha
ER_RM      = er_rm
ER_SRC     = er_src


CC-GNU     = gcc
CC         = ${CC-${CCTYPE}}

SHAREDOPT-DEFAULT	= -Kpic
SHAREDOPT-GNU		= -fpic
SHAREDOPT		= ${SHAREDOPT-${CCTYPE}}

SHAREDLIBOPTS-Solaris   =
SHAREDLIBOPTS-Linux     = -rdynamic
SHAREDLIBOPTS           = $(SHAREDLIBOPTS-$(OSTYPE))

ARCH-DEFAULT-32  =
ARCH-DEFAULT-64  = -xarch=generic64
ARCH-GNU-32      = -m32
ARCH-GNU-64      = -m64
ARCH             = ${ARCH-${CCTYPE}-${WSIZE}}

OPTS 		 = $(ARCH) -xinstrument=datarace -g

LD_FLAGS-DEFAULT = -G ${ARCH}
LD_FLAGS-GNU	 = -shared ${ARCH}
LD_FLAGS	 = ${LD_FLAGS-${CCTYPE}}

LLDLIBS 	 = $(LD_OPTS) -lm -lc

TARGETS= din_philo din_philo_fix1 din_philo_fix2

compile:
	$(CC) din_philo.c -mt -g -o din_philo
	$(CC) din_philo_fix1.c -mt -lrt -g -o din_philo_fix1
	$(CC) din_philo_fix2.c -mt -lrt -g -o din_philo_fix2

collect:
	-$(ER_RM) -f din_philo.er
	-$(COLLECT) -o din_philo.er -r deadlock din_philo

collect_fix1:
	-$(ER_RM) -f din_philo_fix1.er
	-$(COLLECT) -o din_philo_fix1.er -r deadlock din_philo_fix1

collect_fix2:
	-$(ER_RM) -f din_philo_fix2.er
	-$(COLLECT) -o din_philo_fix2.er -r deadlock din_philo_fix2

check: 
	$(ER_PRINT) -deadlock din_philo.er
	$(THA) din_philo.er

check_fix1:
	$(ER_PRINT) -deadlock din_philo_fix1.er
	-$(THA) din_philo_fix1.er

check_fix2:
	$(ER_PRINT) -deadlock din_philo_fix2.er
	-$(THA) din_philo_fix2.er

clean:
	-rm -f $(TARGETS)
	-$(ER_RM) -f *.er
	-rm -f *.o
	-rm -f core*
	-rm -f hs_err_pid*log
	-rm -f ipc_log

veryclean: clean
