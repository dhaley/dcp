####################################################################
#
#		M A K E F I L E
#
#	Makefile for the Rogue Wave Tools.h++ examples
#
#	$Id: makefile.in,v 7.2 1996/03/18 21:33:16 griswolf Exp $
#
#	This file has been processed by the shell script
#	"config_make" to create a CC makefile
#
#  (c) Copyright 1989 - 1996 Rogue Wave Software, Inc.
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

##################################################################
#
#	From here on, it's pretty much boilerplate.
#
##################################################################


SHELL=		/bin/sh
MOVE=		mv
COPY=		ln -s
RM=		rm -f

#	Link directives for the library:
LIBLINK=	-library=rwtools7,iostream

#       Any auxiliary libraries:
AUXLIB=
 
#	Any special flags used by this compiler:
SPECIAL=	

#	Special flags for processing Templates:
TFLAGS=	

#	Compile flags:
CCFLAGS = $(CCOPTIONS) $(TFLAGS)

#	Extension used by this compiler:
EXT =	cpp


##########################    Targets    ########################

tmplcard:
	make CCC=$(CCC) CCFLAGS="$(CCFLAGS)" LIBLINK="$(LIBLINK)" \
		tmplcard_real TARGET=$@

tmplcard_real:
	$(CCC) $(CCFLAGS) $(SPECIAL) -o $(TARGET)  $(TARGET).$(EXT) \
		$(LIBLINK) $(AUXLIB)

.DEFAULT: 
	$(CCC) $(CCFLAGS) $(SPECIAL) -o $<  $<.$(EXT) $(LIBLINK) $(AUXLIB)

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

.SUFFIXES: .cpp .C .c .cc .cxx .o
