# Makefile for "Freeway".
#
# "@(#)Makefile	1.7    99/06/21 SMI"
# Copyright 1991, 1994, 1995, 2000, 2001, 2002 Sun Microsystems, Inc.  All Rights Reserved
#

MOTIFHOME=/usr/dt
CCFLAGS = -g -sb  
CPPFLAGS += -I. -I$(MOTIFHOME)/include 
LDFLAGS += -L$(MOTIFHOME)/lib 
LDLIBS += -lXm -lgen -lXt -lX11 -lsocket 

PROGRAM = Freeway
SOURCES.c =
SOURCES.cc = vehicle.cc main.cc window_ui.cc callbacks.cc traffic.cc\
	vehicle_list.cc truck.cc\
	sports.cc maniac.cc police.cc 
SOURCES.h = maniac.h police.h sports.h truck.h vehicle.h\
	vehicle_list.h window_ui.h about.h traffic.h
GUI.icon = traffic.icon
GUI.bitmap = arrow_left.bitmap arrow_over.bitmap arrow_right.bitmap\
	arrow_up.bitmap traffic.mask

OBJECTS = \
	$(SOURCES.c:%.c=%.o) \
	$(SOURCES.cc:%.cc=%.o) 

# Compiler flags.

debug:=CCFLAGS=-g -sb -xildoff  

# Standard targets.

debug all: $(PROGRAM)
objects: init .WAIT $(OBJECTS)

$(PROGRAM): $(SOURCES.h) $(GUI.icon) $(GUI.bitmap) .WAIT $(OBJECTS)
	LD_RUN_PATH=$(MOTIFHOME)/lib $(LINK.cc) -o $@ $(OBJECTS) $(LDLIBS)
#	LD_RUN_PATH=$(OPENWINHOME)/lib:$(MOTIFHOME)/lib $(LINK.cc) -o $@ $(OBJECTS) $(LDLIBS)

init: $(SOURCES.h) $(GUI.icon) $(GUI.bitmap)

#$(SOURCES.h) $(GUI.icon) $(GUI.bitmap):

clean:
	@-$(RM) -rf .sb $(OBJECTS) $(PROGRAM) \
	  *.BAK *.delta core .prof .nm mon.out \
	  *.tcov *.d tags *~ $(TAG_FILE) SunWS_cache 

recompile: clean all

ctags:
	ctags++ *.cc >/tmp/ctags 2>&1


