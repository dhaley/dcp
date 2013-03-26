# Copyright 2003 Sun Microsystems, Inc.  All Rights Reserved

CCFLAGS= -mt -g -xsb -xildoff

TARGET=tlstest


OBJS=tlstest.o
CPPFLAGS += -I. 
LDFLAGS += -L/usr/lib/lwp -mt 
LDLIBS =  


$(TARGET) : $(OBJS)
	  $(LINK.cc) -o $(@F) $(OBJS) $(LDLIBS)

clean:
	@rm -rf $(OBJS) $(TARGET) $(TARGET).prof $(TARGET).nm \
		mon.out *.tcov *.d tags .sb *~ *% core SunWS_cache
