## makes a shared object: choose the target operating system

OBJECT=cvtXm
EXTRAHDRS=-DXMSTRINGDEFINES=1 -DXTSTRINGDEFINES=1 -I/usr/dt/include -DNO_DEFS_REQUIRED
EXTRALIBS=
EXTRAMOTIFLIB=-L/usr/dt/lib
EXTRAMOTIF64LIB=-L/usr/dt/lib64
EXTRADEFS=-DBROWSER_PROGS=\"mozilla:netscape:firefox:seamonkey:opera:konqueror:safari\"
STDINCLUDES=-I. ${EXTRAHDRS} ${EXTRADEFS}
STDDEFS=-DXDSOBJECTCREATOR=new${OBJECT} -c

HPINCLUDES=-I/usr/include/Motif1.2 -I/usr/include/X11R5
HPR6INCLUDES=-I/usr/include/Motif1.2 -I/usr/include/X11R6
HPLIBS= -ldld -L/usr/lib/Motif1.2 -lXm -L/usr/lib/X11R5 -lXt
HPR6LIBS= -ldld -L/usr/lib/Motif1.2_R6 -lXm -L/usr/lib/X11R6 -lXt
HPCFLAGS=-Aa -D_HPUX_SOURCE -DHP -Wp,-H900000 +DA1.0 +DS1.0
SOLARIS64LIBPATH= -L/usr/dt/lib/sparcv9 -R/usr/dt/lib/sparcv9 -L/usr/openwin/lib/sparcv9 -R/usr/openwin/lib/sparcv9
SOLARIS64AMDLIBPATH= -L/usr/dt/lib/64 -R/usr/dt/lib/64 -L/usr/openwin/lib/64 -R/usr/openwin/lib/64

all:
	@echo "Supported Systems Are:"
	@echo ""
	@echo "solaris"
	@echo "solaris64"
	@echo "solaris64amd"
	@echo "sunos4"
	@echo "hpux"
	@echo "hpux_X11R6"
	@echo "sgi"
	@echo "sgin32"
	@echo "sgio32"
	@echo "sgi64"
	@echo "aix"
	@echo "stdaix"
	@echo "unixware7"
	@echo "lynxos"
	@echo "redhatlinux"
	@echo "linux"
	@echo "linux64"
	@echo "freebsd"
	@echo "osf (Digital Unix)"
	@echo "sco"
	@echo "concurrent (PowerUX 3.1)"

clean:
	-rm -f *.o *.so

RHLINUXFLAGS=-Dlinux -D__i386__ -D__ELF__ -fPIC

redhatlinux:
	-rm -f *.o
	gcc ${RHLINUXFLAGS} -I${MOTIFDIR} ${STDINCLUDES} ${STDDEFS} *.c
	ld -shared *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

LINUXFLAGS=-Dlinux -D__i386__ -D__ELF__ -D_POSIX_SOURCE -fPIC

linux:
	-rm -f *.o
	gcc -m32 ${LINUXFLAGS} -I${MOTIFDIR} ${STDINCLUDES} ${STDDEFS} *.c
	ld -shared *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

linux64:
	-rm -f *.o
	gcc -m64 ${LINUXFLAGS} -I${MOTIFDIR} ${STDINCLUDES} ${STDDEFS} *.c
	ld -shared *.o ${EXTRAMOTIF64LIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

linuxm2:
	-rm -f *.o
	gcc ${LINUXFLAGS} -I/opt/master/joey/tree/Motif2/include ${STDINCLUDES} ${STDDEFS} *.c
	ld -shared *.o -L/opt/master/joey/tree/Motif2/lib ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o


sunos4:
	-rm -f *.o
	cc ${STDINCLUDES}  -I${XDROOT}/lib -I${XDROOT}/lib/X11 ${STDDEFS} -DSUN -DSUN_OS4 -PIC *.c
	/usr/bin/ld -assert nodefinitions -dc -dp *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}-r6.so
	-rm -f *.o
	cc ${STDINCLUDES}  ${STDDEFS} -DSUN -DSUN_OS4 -PIC *.c
	/usr/bin/ld -assert nodefinitions -dc -dp *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}-r5.so
	-rm -f *.o

solaris:
	-rm -f *.o
	cc ${STDINCLUDES}  -I/usr/dt/include -I/usr/openwin/include ${STDDEFS} -DSOLARIS -Xt -KPIC *.c
	ld -G *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

solaris64:
	-rm -f *.o
	cc ${STDINCLUDES}  -I/usr/dt/include -I/usr/openwin/include ${STDDEFS} -DSOLARIS -Xt -KPIC -xarch=v9 *.c
	cc -G -xarch=v9 *.o ${SOLARIS64LIBPATH} ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

solaris64amd:
	-rm -f *.o
	cc ${STDINCLUDES}  -I/usr/dt/include -I/usr/openwin/include ${STDDEFS} -DSOLARIS -Xt -KPIC -xarch=amd64 *.c
	cc -G -xarch=amd64 *.o ${SOLARIS64AMDLIBPATH} ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

solarism2:
	-rm -f *.o
	cc ${STDINCLUDES}  -I/usr/openwin/include ${STDDEFS} -DSOLARIS -Xt -KPIC *.c
	ld -G *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

freebsd:
	-rm -f *.o
	gcc ${STDINCLUDES} ${STDDEFS} *.c
	ld -G *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

unixware7:
	-rm -f *.o
	cc ${STDINCLUDES}  ${STDDEFS} -I/usr/X/include -L/usr/X/lib -K PIC *.c
	ld -G *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

sco:
	-rm -f *.o
	cc ${STDINCLUDES}  ${STDDEFS} -DSCO=1  -I/usr/X/include -L/usr/X/lib -Kpic -dy -b elf *.c
	ld -b elf -G *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

concurrent:
	-rm -f *.o
	cc ${STDINCLUDES}  ${STDDEFS} -I/usr/X/include -L/usr/X/lib -Kpic -dy  *.c
	ld -G *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o


hpux:
	-rm -f *.o
	cc ${STDINCLUDES}  ${HPINCLUDES} ${STDDEFS} ${HPCFLAGS} +Z *.c
	ld -b *.o -B immediate ${HPLIBS} ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.sl
	-rm -f *.o

hpux_X11R6:
	-rm -f *.o
	cc ${STDINCLUDES}  ${HPINCLUDES} ${STDDEFS} ${HPCFLAGS} +Z *.c
	ld -b *.o -B immediate ${HPLIBS} ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.sl
	-rm -f *.o

sgi:
	-rm -f *.o
	cc -cckr -D_XmConst= ${STDINCLUDES}  ${STDDEFS} -KPIC *.c
	ld -shared -soname lib${OBJECT}.so *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

sgim2:
	-rm -f *.o
	cc -cckr -D_XmConst= -I/usr/Motif-2.1/include ${STDINCLUDES}  ${STDDEFS} -KPIC *.c
	ld -shared -soname lib${OBJECT}.so *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

sgin32:
	-rm -f *.o
	cc -n32 -cckr -D_XmConst= ${STDINCLUDES}  ${STDDEFS} -KPIC *.c
	ld -n32 -shared -soname lib${OBJECT}.so *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

sgio32:
	-rm -f *.o
	cc -o32 -cckr -D_XmConst= ${STDINCLUDES}  ${STDDEFS} -KPIC *.c
	ld -o32 -shared -soname lib${OBJECT}.so *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o

sgi64:
	-rm -f *.o
	cc -64 -cckr -D_XmConst= ${STDINCLUDES}  ${STDDEFS} -KPIC *.c
	ld -64 -shared -soname lib${OBJECT}.so *.o ${EXTRAMOTIFLIB} ${EXTRALIBS}
	mv a.out lib${OBJECT}.so
	-rm -f *.o


osf:
	-rm -f *.o
	cc ${STDINCLUDES}  ${STDDEFS} *.c
	ld -shared -soname lib${OBJECT}.so *.o ${EXTRAMOTIFLIB} ${EXTRALIBS} -lc
	mv a.out lib${OBJECT}.so
	-rm -f *.o


lynxos:
	-rm -f *.o *.a
	gcc ${STDINCLUDES}  ${STDDEFS} *.c
	ar rv lib${OBJECT}.a *.o
	ranlib lib${OBJECT}.a
	-rm -f *.o

aix:
	-rm -f *.a
## share objects need import and export files in aixhook subdir.
	test -s aixhook/${OBJECT}.exp
	test -s aixhook/${OBJECT}.imp
	cc ${STDINCLUDES}  ${STDDEFS} *.c
	ld -bM:SRE -H512 -T512 -bnoentry -o shr4.o -bE:aixhook/${OBJECT}.exp -bI:aixhook/${OBJECT}.imp *.o ${EXTRAMOTIFLIB} ${EXTRALIBS} -lc
	mv shr4.o shr4.obj
	rm -f *.o
	mv shr4.obj shr4.o
	ar rv lib${OBJECT}.a shr4.o
	-rm -f *.o
	@echo "The aix shared object is lib${OBJECT}.a"


stdaix:
	-rm -f *.o
	cc ${STDINCLUDES}  ${STDDEFS} *.c
	ld -o shr4.o -G -bexpall *.o ${EXTRAMOTIFLIB} ${EXTRALIBS} -lc
	mv shr4.o shr4.obj
	rm -f *.o
	mv shr4.obj shr4.o
	ar rv lib${OBJECT}.a shr4.o
	-rm -f *.o
	@echo "The stdaix shared object is lib${OBJECT}.a"

stdaixm2:
	-rm -f *.o
	cc -I/usr/include/Motif2.1 ${STDINCLUDES}  ${STDDEFS} *.c
	ld -bM:SRE -H512 -T512 -bnoentry -o shr4.o -bE:aixhook/${OBJECT}.exp -bI:aixhook/${OBJECT}.imp *.o ${EXTRAMOTIFLIB} ${EXTRALIBS} -lc
	mv shr4.o shr4.obj
	rm -f *.o
	mv shr4.obj shr4.o
	ar rv lib${OBJECT}.a shr4.o
	-rm -f *.o
	@echo "The stdaixm2 shared object is lib${OBJECT}.a"
