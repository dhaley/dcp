####################################################################
#
#		M A K E F I L E
#
#	Makefile template for the Rogue Wave Tools.h++ examples
#
#  (c) Copyright 1989 - 1995 Rogue Wave Software, Inc.
#  ALL RIGHTS RESERVED

#
#  The software and information contained herein are proprietary to, and
#  comprise valuable trade secrets of, Rogue Wave Software, Inc., which
#  intends to preserve as trade secrets such software and information.
#  This software is furnished pursuant to a written license agreement and
#  may be used, copied, transmitted, and stored only in accordance with
#  the terms of such license and with the inclusion of the above copyright
#  notice.  This software and information or any other copies thereof may
#  not be provided or otherwise made available to any other person.
#
#  Notwithstanding any other lease or license that may pertain to, or
#  accompany the delivery of, this computer software and information, the
#  rights of the Government regarding its use, reproduction and disclosure
#  are as set forth in Section 52.227-19 of the FARS Computer
#  Software-Restricted Rights clause.
#
#  Use, duplication, or disclosure by the Government is subject to
#  restrictions as set forth in subparagraph (c)(1)(ii) of the Rights in
#  Technical Data and Computer Software clause at DFARS 252.227-7013.
#  Contractor/Manufacturer is Rogue Wave Software, Inc.,
#  P.O. Box 2328, Corvallis, Oregon 97339.
#
#  This computer software and information is distributed with "restricted
#  rights."  Use, duplication or disclosure is subject to restrictions as
#  set forth in NASA FAR SUP 18-52.227-79 (April 1985) "Commercial
#  Computer Software-Restricted Rights (April 1985)."  If the Clause at
#  18-52.227-74 "Rights in Data General" is specified in the contract,
#  then the "Alternate III" clause applies.
#
#==========================================================================
#  
####################################################################

CCC=		CC

#	Options to be passed to your C++ compiler:
CCOPTIONS=	-O

#	Where the library is located:
LIBDIR=		../lib

#	Rogue Wave header file include path:
RWINCL=		..

#	STL header include path
STLINCL=


#	Full path to the library:
LIBFULL=	$(LIBDIR)/librwtool.a

#	Link directives for the library:
LIBLINK=


#	Compile flags:
CPPFLAGS= 	-I$(RWINCL) $(STLINCL) $(CCOPTIONS) -library=rwtools7,iostream


########################   Executables    #######################

SIMPLE=		timedate cstring gdlist binaryt hashdict \
		btreedsk fmgrsave fmgrrtrv pageheap bus 

#               STL based examples: 
STL=		mmapptr dequeval

#		Template example programs:
TEMPLATE=	tvdlist  tpdlist

#		Internationalization example programs:
I18N=		i18n

EXAMPLES=	$(SIMPLE)

##########################    Targets    ########################

all:	$(EXAMPLES)

timedate:	timedate.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

cstring:	cstring.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

gdlist:		gdlist.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

binaryt:	binaryt.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

hashdict:	hashdict.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

btreedsk:	btreedsk.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

fmgrsave:	fmgrsave.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

fmgrrtrv:	fmgrrtrv.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

pageheap:	pageheap.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

bus:		bus.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

tvdlist:	tvdlist.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

tpdlist:	tpdlist.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

i18n:		i18n.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

dequeval:	dequeval.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)
	
mmapptr:	mmapptr.o
	$(CCC)  $(CPPFLAGS) -o $@ $@.o $(LIBLINK)

clean:
	$(RM) *.o
	$(RM) *..dbx
	$(RM) *.i
	$(RM) *.ixx
	$(RM) $(EXAMPLES)
	$(RM) *.dat
	$(RM) *.bin
	$(RM) *.str

##########################  Conversions   ########################

.SUFFIXES: .cpp .C .cc .cxx .o


##################################################
# general case for compilation
%.o: %.cpp	
	$(CCC) $(CCFLAGS) $(CPPFLAGS)  -c -o $@ $<

