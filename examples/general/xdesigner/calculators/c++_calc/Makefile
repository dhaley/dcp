# File: Makefile
#
# This is a makefile for use with CC
#
CC = CC

.SUFFIXES: .c .o .h
FLAGS = -DDEBUG

INCDIRS = -I.  -I/usr/openwin/include -I/usr/dt/include

LIBDIRS = -L/usr/openwin/lib -L/usr/dt/lib -R/usr/openwin/lib -R/usr/dt/lib

LIBS=  -lXm -lXt -lX11

#
# Standard sources and objects
#
EXEC = CalcDemo
HDRS = Value.h Nodes.h CalcDemo.h xdclass.h
SRCS = Value.c NodeParse.c CalcDialog.c CalcDemo.c xdxtclass.c xdxmdialog.c
OBJS = Value.o NodeParse.o CalcDialog.o CalcDemo.o xdxtclass.o xdxmdialog.o
#
# Rules for normal comile and link 
#
.c.o:
	$(CC) -g -c $(INCDIRS) $<

all::   $(EXEC)

Value.o NodeParse.o : Value.h Nodes.h

CalcDialog.o CalcDemo.o : CalcDemo.h

xdxtclass.o xdxmdialog.o : xdclass.h

$(EXEC): $(OBJS) 
	$(CC) -o $(EXEC) $(FLAGS) $(OBJS) $(LIBDIRS) $(LIBS) -lm

clean:
	rm -f *.o *.bak core *.a $(EXEC)
