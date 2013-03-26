
# Explicit setting of SHELL - beware since this gets inherited
# by commands invoked by Make

SHELL=/bin/sh
TARGET=generic
ABIDIR=
SYSDIR=
ABICFLAGS=
ABICCFLAGS=
ABILDFLAGS=

# Default rule
all: all-${TARGET}

#: system Solaris 32bit Workshop4 Compatible C++
#: default c
# No User Defined Widgets configured
MOTIFHOME=/usr/dt
MOTIFINCLUDES=-I${MOTIFHOME}/include
XINCLUDES=${MOTIFINCLUDES} -I/usr/openwin/include -I/usr/openwin/include/X11
SYSDEFS=-DUSL -DSYSV
CPPFLAGS=-Ddrem=remainder -DS_SUNOS5
ABI1CFLAGS=
ABI1CCFLAGS=-compat=4
ABI1LDFLAGS=
ABI1ABIDIR=/compat-pre5
ABI1SYSDIR=
ABICFLAGS=${ABI1CFLAGS}
ABICCFLAGS=${ABI1CCFLAGS}
ABILDFLAGS=${ABI1LDFLAGS}
SYSDIR=
ABIDIR=/compat-pre5
#: end


CFLAGS=
IFLAGS=${SYSDEFS} ${XINCLUDES}

.c.o:
	rm -f $@
	cc -c $(CPPFLAGS) $(CFLAGS) $(IFLAGS) $*.c

all-generic:    helplink.o

