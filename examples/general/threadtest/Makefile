# Copyright 2002 Sun Microsystems, Inc.  All Rights Reserved

CCFLAGS= -mt -g -xsb -xildoff

TARGET=threadtest


OBJS=threadtest.o
CPPFLAGS += -I. -I$(MOTIFHOME)/include
LDFLAGS += -L$(MOTIFHOME)/lib
LDLIBS += -lXm -lgen -lXt -lX11 


$(TARGET) : $(OBJS)
	  $(LINK.cc) -o $(@F) $(OBJS) $(LDLIBS)

clean:
	@rm -rf $(OBJS) $(TARGET) $(TARGET).prof $(TARGET).nm \
		mon.out *.tcov *.d tags .sb *~ *% core SunWS_cache
