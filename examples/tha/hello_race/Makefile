# Copyright 04/17/07 Sun Microsystems, Inc. All Rights Reserved
# @(#)Makefile 1.2 07/04/17 SMI


EXE      = hello_race.exe
OBJ      = hello_race.o
CFLAGS   = -c -g -xopenmp=noopt -xinstrument=datarace
LDFLAGS  = -xopenmp=noopt -xinstrument=datarace

CC       = cc
COLLECT  = collect
ER_PRINT = er_print
THA      = tha
ER_RM    = er_rm
ER_SRC   = er_src


.IGNORE:

default:
	make $(EXE)

demo: $(EXE)
	(OMP_DYNAMIC=FALSE; export OMP_DYNAMIC; \
	OMP_NUM_THREADS=4; export OMP_NUM_THREADS ;\
	$(ER_RM) -f race.er ;\
	$(COLLECT) -o race.er -r race ./$(EXE) ;\
	$(THA) race.er)

$(EXE): $(OBJ)
	$(CC) -o $(EXE) $(OBJ) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) $*.c

clean:
	@/bin/rm -rf $(EXE) $(OBJ)
	@/bin/rm -rf *.er
