# Copyright 2002,2003 Sun Microsystems, Inc. All Rights Reserved
#
# Makefile for the 64-bit program
#


# Compile in 64-bit mode by uncommenting the first line; comment out the
# other one.
#ARCH = -xarch=v9
ARCH =


OFLAGS = -g -v -DDEBUG 
#OFLAGS = -g -v

OPTS = $(OFLAGS) $(ARCH)


TARGETS= 64bit

SRCS= generate.c    \
	interface.c \
	io.c        \
	main.c      \
	sort.c      \
	$(NULL)

DEPEND= common.h \
	$(NULL)

OBJS= ${SRCS:.o .c} \
	$(NULL)

default all:
	@$(MAKE) $(TARGETS)

$(TARGETS): $(SRCS) $(DEPEND)
	-cc $(OPTS) -o $@ $(SRCS) 

clean:
	-rm -f $(TARGETS)
	-rm -f *.o
	-rm -f core*
