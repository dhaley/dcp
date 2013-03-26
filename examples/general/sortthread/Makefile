.KEEP_STATE:

%.class: %.java
	javac -g -deprecation $<


%.h: %.class
	javah -jni $* # -o $@

# javasofts jdk:
JDK_HOME = /usr/jdk/j2sdk1.4.2_06

IFLAGS += -I$(JDK_HOME)/include
IFLAGS += -I$(JDK_HOME)/include/solaris
CFLAGS += $(IFLAGS) -v -g
CCFLAGS += $(IFLAGS)  -mt -g
SOMAKER = cc -G

all : classes libSortThread.so
CLASSES = 
TESTS = SortThread.class
classes : $(CLASSES) $(TESTS)

libSortThread.so := IFLAGS += -I$(JDK_HOME)/include
libSortThread.so := IFLAGS += -I$(JDK_HOME)/include/solaris 
libSortThread.so := CFLAGS += -mt
SortThread_O = SortThread.o
libSortThread.so : $(SortThread_O)
	$(SOMAKER) -o libSortThread.so $(SortThread_O)

$(SortThread_O): SortThread.c
	$(SOMAKER) $(CCFLAGS) -c SortThread.c

clean :
	rm -f *.o *.so *.class *.h
