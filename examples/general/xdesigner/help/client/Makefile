
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

##: system Solaris 32bit Ansi C/C++
##: default cpp
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr/dt
#MOTIFINCLUDES=-I${MOTIFHOME}/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/openwin/include -I/usr/openwin/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_SUNOS5
#ABI2CFLAGS=
#ABI2CCFLAGS=-compat=5 -features=no%conststrings
#ABI2LDFLAGS=
#ABI2ABIDIR=/ansi32
#ABI2SYSDIR=
#ABICFLAGS=${ABI2CFLAGS}
#ABICCFLAGS=${ABI2CCFLAGS}
#ABILDFLAGS=${ABI2LDFLAGS}
#SYSDIR=
#ABIDIR=/ansi32
##: end

##: system Solaris 64bit Ansi C/C++ (sparc)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr/dt
#MOTIFINCLUDES=-I${MOTIFHOME}/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/openwin/include -I/usr/openwin/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_SUNOS5
#ABI2-64CFLAGS=-xarch=v9
#ABI2-64CCFLAGS=-xarch=v9 -compat=5
#ABI2-64LDFLAGS=
#ABI2-64ABIDIR=/sparcv9
#ABI2-64SYSDIR=/sparcv9
#ABICFLAGS=${ABI2-64CFLAGS}
#ABICCFLAGS=${ABI2-64CCFLAGS}
#ABILDFLAGS=${ABI2-64LDFLAGS}
#SYSDIR=/sparcv9
#ABIDIR=/sparcv9
##: end

##: system Solaris 32bit Workshop4 Compatible C++
##: default c
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr/dt
#MOTIFINCLUDES=-I${MOTIFHOME}/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/openwin/include -I/usr/openwin/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_SUNOS5
#ABI1CFLAGS=
#ABI1CCFLAGS=-compat=4
#ABI1LDFLAGS=
#ABI1ABIDIR=/compat-pre5
#ABI1SYSDIR=
#ABICFLAGS=${ABI1CFLAGS}
#ABICCFLAGS=${ABI1CCFLAGS}
#ABILDFLAGS=${ABI1LDFLAGS}
#SYSDIR=
#ABIDIR=/compat-pre5
##: end

##: system Solaris 64bit AMD C/C++ (opteron)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr/dt
#MOTIFINCLUDES=-I${MOTIFHOME}/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/openwin/include -I/usr/openwin/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_SUNOS5
#AMD-64CFLAGS=-xarch=amd64
#AMD-64CCFLAGS=-xarch=amd64 -compat=5
#AMD-64LDFLAGS=
#AMD-64ABIDIR=/amd64
#AMD-64SYSDIR=/amd64
#ABICFLAGS=${AMD-64CFLAGS}
#ABICCFLAGS=${AMD-64CCFLAGS}
#ABILDFLAGS=${AMD-64LDFLAGS}
#SYSDIR=/amd64
#ABIDIR=/amd64
##: end

##: system Solaris 32/64 Multi-target C/C++
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr/dt
#MOTIFINCLUDES=-I${MOTIFHOME}/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/openwin/include -I/usr/openwin/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_SUNOS5
## Extra ABI targets for solaris2_abi_multiabi
#ABI1CFLAGS=
#ABI1CCFLAGS=-compat=4
#ABI1LDFLAGS=
#ABI1ABIDIR=/compat-pre5
#ABI1SYSDIR=
#
#all-compat-pre5::
#	make -f Makefile TARGET=generic ABICFLAGS="${ABI1CFLAGS}" ABICCFLAGS="${ABI1CCFLAGS}" ABILDFLAGS="${ABI1LDFLAGS}" ABIDIR="/${ABI1ABIDIR}" SYSDIR="${ABI1SYSDIR}" all
#
#server-compat-pre5::
#	make -f Makefile TARGET=generic ABICFLAGS="${ABI1CFLAGS}" ABICCFLAGS="${ABI1CCFLAGS}" ABILDFLAGS="${ABI1LDFLAGS}" ABIDIR="/${ABI1ABIDIR}" SYSDIR="${ABI1SYSDIR}" server
#
#ABI2CFLAGS=
#ABI2CCFLAGS=-compat=5 -features=no%conststrings
#ABI2LDFLAGS=
#ABI2ABIDIR=/ansi32
#ABI2SYSDIR=
#
#all-ansi32::
#	make -f Makefile TARGET=generic ABICFLAGS="${ABI2CFLAGS}" ABICCFLAGS="${ABI2CCFLAGS}" ABILDFLAGS="${ABI2LDFLAGS}" ABIDIR="/${ABI2ABIDIR}" SYSDIR="${ABI2SYSDIR}" all
#
#server-ansi32::
#	make -f Makefile TARGET=generic ABICFLAGS="${ABI2CFLAGS}" ABICCFLAGS="${ABI2CCFLAGS}" ABILDFLAGS="${ABI2LDFLAGS}" ABIDIR="/${ABI2ABIDIR}" SYSDIR="${ABI2SYSDIR}" server
#
#ABI2-64CFLAGS=-xarch=v9
#ABI2-64CCFLAGS=-xarch=v9 -compat=5
#ABI2-64LDFLAGS=
#ABI2-64ABIDIR=/sparcv9
#ABI2-64SYSDIR=/sparcv9
#
#all-sparcv9::
#	make -f Makefile TARGET=generic ABICFLAGS="${ABI2-64CFLAGS}" ABICCFLAGS="${ABI2-64CCFLAGS}" ABILDFLAGS="${ABI2-64LDFLAGS}" ABIDIR="/${ABI2-64ABIDIR}" SYSDIR="${ABI2-64SYSDIR}" all
#
#server-sparcv9::
#	make -f Makefile TARGET=generic ABICFLAGS="${ABI2-64CFLAGS}" ABICCFLAGS="${ABI2-64CCFLAGS}" ABILDFLAGS="${ABI2-64LDFLAGS}" ABIDIR="/${ABI2-64ABIDIR}" SYSDIR="${ABI2-64SYSDIR}" server
#
#compatCFLAGS=
#compatCCFLAGS=
#compatLDFLAGS=
#compatABIDIR=/pre5
#compatSYSDIR=
#
#all-pre5::
#	make -f Makefile TARGET=generic ABICFLAGS="${compatCFLAGS}" ABICCFLAGS="${compatCCFLAGS}" ABILDFLAGS="${compatLDFLAGS}" ABIDIR="/${compatABIDIR}" SYSDIR="${compatSYSDIR}" all
#
#server-pre5::
#	make -f Makefile TARGET=generic ABICFLAGS="${compatCFLAGS}" ABICCFLAGS="${compatCCFLAGS}" ABILDFLAGS="${compatLDFLAGS}" ABIDIR="/${compatABIDIR}" SYSDIR="${compatSYSDIR}" server
#
#AMD-64CFLAGS=-xarch=amd64
#AMD-64CCFLAGS=-xarch=amd64 -compat=5
#AMD-64LDFLAGS=
#AMD-64ABIDIR=/amd64
#AMD-64SYSDIR=/amd64
#
#all-amd64::
#	make -f Makefile TARGET=generic ABICFLAGS="${AMD-64CFLAGS}" ABICCFLAGS="${AMD-64CCFLAGS}" ABILDFLAGS="${AMD-64LDFLAGS}" ABIDIR="/${AMD-64ABIDIR}" SYSDIR="${AMD-64SYSDIR}" all
#
#server-amd64::
#	make -f Makefile TARGET=generic ABICFLAGS="${AMD-64CFLAGS}" ABICCFLAGS="${AMD-64CCFLAGS}" ABILDFLAGS="${AMD-64LDFLAGS}" ABIDIR="/${AMD-64ABIDIR}" SYSDIR="${AMD-64SYSDIR}" server
#
##: end

##: system HP-UX 11.x
## -Wp,-H900000 recommended if too many cpp defines.
## For K&R code generation use:
## CPPFLAGS=-Wp,-H900000
## For ANSI C code generation use:
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=
#MOTIFINCLUDES=-I/usr/include/Motif2.1
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11R6 -I/usr/include/X11R6/X11
#CPPFLAGS=-Wp,-H900000 -Aa -D_HPUX_SOURCE -Ddrem=remainder  -DS_HPUX
##: end

##: system HP-UX 10.x
## -Wp,-H900000 recommended if too many cpp defines.
## For K&R code generation use:
## CPPFLAGS=-Wp,-H900000
## For ANSI C code generation use:
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=
#MOTIFINCLUDES=-I/usr/include/Motif1.2
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11R6 -I/usr/include/X11R6/X11
#CPPFLAGS=-Wp,-H900000 -Aa -D_HPUX_SOURCE -Ddrem=remainder  -DS_HPUX
##: end

##: system HP-UX 9.x
## -Wp,-H900000 recommended if too many cpp defines.
## For K&R code generation use:
## CPPFLAGS=-Wp,-H900000
## For ANSI C code generation use:
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=
#MOTIFINCLUDES=-I/usr/include/Motif2.1
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11R6
#CPPFLAGS=-Wp,-H900000 -Aa -D_HPUX_SOURCE -DS_HPUX
##: end

##: system IBM Aix
# No User Defined Widgets configured
#RANLIB=ranlib
#MOTIFHOME=
#MOTIFINCLUDES=
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-DS_AIX
##: end

##: system Compaq "Digital Unix"
# No User Defined Widgets configured
#RANLIB=ranlib
#MOTIFHOME=
#MOTIFINCLUDES=
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-DS_DIGITAL
##: end

##: system Concurrent (MAXION System 5 Release 4)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=
#MOTIFINCLUDES=
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-DS_CONCURRENT
##: end

##: system NCR (System 5 Release 4)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=
#MOTIFINCLUDES=
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_NCR
##: end

##: system NEC (System 5 Release 4)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=
#MOTIFINCLUDES=
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_NEC
##: end

##: system SCO UnixWare 7 (was Novell)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=
#MOTIFINCLUDES=
#XINCLUDES=${MOTIFINCLUDES} -I/usr/X/include -I/usr/X/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_UNIXWARE
##: end

##: system HAL Solaris 2.x
## For ANSI C code generation use:
## CPPFLAGS=-KV7 -Xa
# No User Defined Widgets configured
#RANLIB=ranlib
#MOTIFHOME=/usr/dt
#MOTIFINCLUDES=-I${MOTIFHOME}/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/openwin/include -I/usr/openwin/include/X11
#CPPFLAGS=-KV7 -Xk  -DSUNOS5
##: end

##: system Silicon Graphics (new 32 bit)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr
#MOTIFINCLUDES=-I${MOTIFHOME}/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_IRIX
#n32CFLAGS=-n32
#n32CCFLAGS=-n32
#n32LDFLAGS=-n32
#n32ABIDIR=/n32
#n32SYSDIR=32
#ABICFLAGS=${n32CFLAGS}
#ABICCFLAGS=${n32CCFLAGS}
#ABILDFLAGS=${n32LDFLAGS}
#SYSDIR=32
#ABIDIR=/n32
##: end

##: system Silicon Graphics (new 64 bit)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr
#MOTIFINCLUDES=-I${MOTIFHOME}/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_IRIX
#n64CFLAGS=-64
#n64CCFLAGS=-64
#n64LDFLAGS=-64
#n64ABIDIR=/n64
#n64SYSDIR=64
#ABICFLAGS=${n64CFLAGS}
#ABICCFLAGS=${n64CCFLAGS}
#ABILDFLAGS=${n64LDFLAGS}
#SYSDIR=64
#ABIDIR=/n64
##: end

##: system Silicon Graphics (old 32 bit)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr
#MOTIFINCLUDES=-I${MOTIFHOME}/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_IRIX
#o32CFLAGS=-o32
#o32CCFLAGS=-o32
#o32LDFLAGS=-o32
#o32ABIDIR=/o32
#o32SYSDIR=
#ABICFLAGS=${o32CFLAGS}
#ABICCFLAGS=${o32CCFLAGS}
#ABILDFLAGS=${o32LDFLAGS}
#SYSDIR=
#ABIDIR=/o32
##: end

##: system Silicon Graphics (Irix 6.5 Defaults)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr
#MOTIFINCLUDES=-I${MOTIFHOME}/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_IRIX
#dfltCFLAGS=-n32
#dfltCCFLAGS=-n32
#dfltLDFLAGS=-n32
#dfltABIDIR=/n32
#dfltSYSDIR=32
#ABICFLAGS=${dfltCFLAGS}
#ABICCFLAGS=${dfltCCFLAGS}
#ABILDFLAGS=${dfltLDFLAGS}
#SYSDIR=32
#ABIDIR=/n32
##: end

##: system Silicon Graphics (Pre 6.5 Defaults)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr
#MOTIFINCLUDES=-I${MOTIFHOME}/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_IRIX
#tradCFLAGS=-o32
#tradCCFLAGS=-o32
#tradLDFLAGS=-o32
#tradABIDIR=/o32
#tradSYSDIR=
#ABICFLAGS=${tradCFLAGS}
#ABICCFLAGS=${tradCCFLAGS}
#ABILDFLAGS=${tradLDFLAGS}
#SYSDIR=
#ABIDIR=/o32
##: end

##: system Silicon Graphics 32/64 Multi-target C/C++
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr
#MOTIFINCLUDES=-I${MOTIFHOME}/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-Ddrem=remainder -DS_IRIX
## Extra ABI targets for sg_irix_abi_multiabi
#o32CFLAGS=-o32
#o32CCFLAGS=-o32
#o32LDFLAGS=-o32
#o32ABIDIR=/o32
#o32SYSDIR=
#
#all-o32::
#	make -f Makefile TARGET=generic ABICFLAGS="${o32CFLAGS}" ABICCFLAGS="${o32CCFLAGS}" ABILDFLAGS="${o32LDFLAGS}" ABIDIR="/${o32ABIDIR}" SYSDIR="${o32SYSDIR}" all
#
#server-o32::
#	make -f Makefile TARGET=generic ABICFLAGS="${o32CFLAGS}" ABICCFLAGS="${o32CCFLAGS}" ABILDFLAGS="${o32LDFLAGS}" ABIDIR="/${o32ABIDIR}" SYSDIR="${o32SYSDIR}" server
#
#n32CFLAGS=-n32
#n32CCFLAGS=-n32
#n32LDFLAGS=-n32
#n32ABIDIR=/n32
#n32SYSDIR=32
#
#all-n32::
#	make -f Makefile TARGET=generic ABICFLAGS="${n32CFLAGS}" ABICCFLAGS="${n32CCFLAGS}" ABILDFLAGS="${n32LDFLAGS}" ABIDIR="/${n32ABIDIR}" SYSDIR="${n32SYSDIR}" all
#
#server-n32::
#	make -f Makefile TARGET=generic ABICFLAGS="${n32CFLAGS}" ABICCFLAGS="${n32CCFLAGS}" ABILDFLAGS="${n32LDFLAGS}" ABIDIR="/${n32ABIDIR}" SYSDIR="${n32SYSDIR}" server
#
#n64CFLAGS=-64
#n64CCFLAGS=-64
#n64LDFLAGS=-64
#n64ABIDIR=/n64
#n64SYSDIR=64
#
#all-n64::
#	make -f Makefile TARGET=generic ABICFLAGS="${n64CFLAGS}" ABICCFLAGS="${n64CCFLAGS}" ABILDFLAGS="${n64LDFLAGS}" ABIDIR="/${n64ABIDIR}" SYSDIR="${n64SYSDIR}" all
#
#server-n64::
#	make -f Makefile TARGET=generic ABICFLAGS="${n64CFLAGS}" ABICCFLAGS="${n64CCFLAGS}" ABILDFLAGS="${n64LDFLAGS}" ABIDIR="/${n64ABIDIR}" SYSDIR="${n64SYSDIR}" server
#
##: end

##: system SCO OpenServer 5
# No User Defined Widgets configured
#RANLIB=ranlib
#MOTIFHOME=
#MOTIFINCLUDES=
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-DSCO -DS_SCO
##: end

##: system QNX
# No User Defined Widgets configured
#RANLIB=ranlib
#MOTIFHOME=
#MOTIFINCLUDES=
#XINCLUDES=${MOTIFINCLUDES} 	-I/usr/include/X11
#CPPFLAGS=-DQNX -DS_QNX
##: end

##: system Lynx Real-Time OS (PPC)
# No User Defined Widgets configured
#RANLIB=ranlib
#MOTIFHOME=
#MOTIFINCLUDES=
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-DLYNX -DS_LYNXOS
##: end

##: system Linux (x86 64 bit)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr/OpenMotif-2.1.31
#MOTIFINCLUDES=-I$(MOTIFHOME)/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/X11R6/include -I/usr/X11R6/include/X11
#CPPFLAGS=-DS_LINUX
#X86_64CFLAGS=-m64
#X86_64CCFLAGS=-m64
#X86_64LDFLAGS=
#X86_64ABIDIR=/lib64
#X86_64SYSDIR=64
#ABICFLAGS=${X86_64CFLAGS}
#ABICCFLAGS=${X86_64CCFLAGS}
#ABILDFLAGS=${X86_64LDFLAGS}
#SYSDIR=64
#ABIDIR=/lib64
##: end

##: system Linux (x86)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr/OpenMotif-2.1.31
#MOTIFINCLUDES=-I$(MOTIFHOME)/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/X11R6/include -I/usr/X11R6/include/X11
#CPPFLAGS=-DS_LINUX
#X86CFLAGS=-m32
#X86CCFLAGS=-m32
#X86LDFLAGS=
#X86ABIDIR=/lib32
#X86SYSDIR=
#ABICFLAGS=${X86CFLAGS}
#ABICCFLAGS=${X86CCFLAGS}
#ABILDFLAGS=${X86LDFLAGS}
#SYSDIR=
#ABIDIR=/lib32
##: end

##: system Linux 32/64 Multi-target C/C++
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=/usr/OpenMotif-2.1.31
#MOTIFINCLUDES=-I$(MOTIFHOME)/include
#XINCLUDES=${MOTIFINCLUDES} -I/usr/X11R6/include -I/usr/X11R6/include/X11
#CPPFLAGS=-DS_LINUX
## Extra ABI targets for linux_abi_multiabi
#X86CFLAGS=-m32
#X86CCFLAGS=-m32
#X86LDFLAGS=
#X86ABIDIR=/lib32
#X86SYSDIR=
#
#all-lib32::
#	make -f Makefile TARGET=generic ABICFLAGS="${X86CFLAGS}" ABICCFLAGS="${X86CCFLAGS}" ABILDFLAGS="${X86LDFLAGS}" ABIDIR="/${X86ABIDIR}" SYSDIR="${X86SYSDIR}" all
#
#server-lib32::
#	make -f Makefile TARGET=generic ABICFLAGS="${X86CFLAGS}" ABICCFLAGS="${X86CCFLAGS}" ABILDFLAGS="${X86LDFLAGS}" ABIDIR="/${X86ABIDIR}" SYSDIR="${X86SYSDIR}" server
#
#X86_64CFLAGS=-m64
#X86_64CCFLAGS=-m64
#X86_64LDFLAGS=
#X86_64ABIDIR=/lib64
#X86_64SYSDIR=64
#
#all-lib64::
#	make -f Makefile TARGET=generic ABICFLAGS="${X86_64CFLAGS}" ABICCFLAGS="${X86_64CCFLAGS}" ABILDFLAGS="${X86_64LDFLAGS}" ABIDIR="/${X86_64ABIDIR}" SYSDIR="${X86_64SYSDIR}" all
#
#server-lib64::
#	make -f Makefile TARGET=generic ABICFLAGS="${X86_64CFLAGS}" ABICCFLAGS="${X86_64CCFLAGS}" ABILDFLAGS="${X86_64LDFLAGS}" ABIDIR="/${X86_64ABIDIR}" SYSDIR="${X86_64SYSDIR}" server
#
##: end

##: system Concurrent Night Hawk (PowerUX3.1)
# No User Defined Widgets configured
#RANLIB=@:
#MOTIFHOME=
#MOTIFINCLUDES=
#XINCLUDES=${MOTIFINCLUDES} -I/usr/include/X11
#CPPFLAGS=-DS_POWERUX
##: end

all-generic: lib.a

lib.a:		help.c
		cc -c $(CPPFLAGS) $(XINCLUDES) help.c
		ar ruv lib.a help.o
		-$(RANLIB) lib.a

help.c:	help.h path.h

clean:;		rm -f *.o lib.a

