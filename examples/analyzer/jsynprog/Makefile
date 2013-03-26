# Copyright 02/12/07 Sun Microsystems, Inc. All Rights Reserved
#
# @(#)Makefile 1.14 07/02/12 SMI

###########################################################
#
#  The next few lines are setting that you should edit to change
#	which compilers, and options you use to build
###########################################################

# Set JAVABIN to point at the path to a JVM, 1.4.2_02 or later, to build
JAVABIN=/usr/java/bin

OS = solaris
# Uncomment out the next line to compile on linux
# OS = linux

CCTYPE = DEFAULT
# Uncomment out the next line to compile using GNU compiler
# CCTYPE = GNU

# Select an architecture (32/64 bit), for the compiler type chosen, and comment out the others
WSIZE = 32
#WSIZE = 64

###########################################################

CC-DEFAULT      = cc
CC-GNU          = gcc
CC              = ${CC-${CCTYPE}}

CCC-DEFAULT     = CC 
CCC-GNU         = g++
CCC             = ${CCC-${CCTYPE}}

ARCH            = -m${WSIZE}

COPTS-DEFAULT 	=-G -g -V
COPTS-GNU       =-shared -g -Wall -v -fPIC
COPTS           = ${COPTS-${CCTYPE}} ${ARCH}

JAVA_MODEL-32   =
JAVA_MODEL-64   = -d64
JAVA_MODEL      = ${JAVA_MODEL-${WSIZE}}

JAVA=$(JAVABIN)/java
JAVAC=$(JAVABIN)/javac
JAVA_INCLUDE=-I$(JAVABIN)/../include -I$(JAVABIN)/../include/$(OS)
LIBCLOOP-32     = libcloop.so
LIBCLOOP-64     = libcloop64.so
TARGETS= ${LIBCLOOP-${WSIZE}} jsynprog.class

SRCS= \
	gethrtime.c \
	cloop.cc \
	$(NULL)

JAVA_SRCS= \
	Intface.java \
	Routine.java \
	Sub_Routine.java \
	jsynprog.java \
	Launcher.java \
	$(NULL)

all:	$(TARGETS)
	@echo " ----DONE: $@ -----"

libcloop.so libcloop64.so: $(SRCS) 
	$(CCC) $(COPTS) -o $@ $(JAVA_INCLUDE) $(SRCS)

jsynprog.class: $(JAVA_SRCS)
	$(JAVAC) $(JAVA_SRCS) 

clean:
	-rm -f *.o
	-rm -f *.so
	-rm -f core

clobber: clean
	-rm -f $(TARGETS) $(LIBCLOOP-32) $(LIBCLOOP-64)
	-er_rm -f test*.er
	-rm -rf SunWS_cache
	-rm -rf jsynprog.acct 
	-rm -f *.class
	-rm -f core*
	-rm -f hs_err*.log

run: $(TARGETS)
	$(JAVA) $(JAVA_MODEL) jsynprog

collect: $(TARGETS)
	collect -j on $(JAVA) jsynprog
