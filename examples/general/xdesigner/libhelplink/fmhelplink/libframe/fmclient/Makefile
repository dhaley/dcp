# $Id: Makefile,v 1.7 1991/06/15 21:19:49 sxg Exp $
# Makefile for fmbitmap.
#
# Note: the following items must be supplied by the user:
# rpcgen from Sun RPC version 3.9.
# /usr/lib/libXm.a from Motif 1.0 source.
# /usr/lib/libXt.a from Motif 1.0 source.
# Rpc and Motif header files.

# Insert -I flags into PLAT_FLAGS to find the Motif and Xt include files.
# Insert -L flags into LIBS to find the Motif and Xt library archives.

#Sun# PLAT_FLAGS = -I/usr/local/include
#SUN4LIBS = -Bstatic
#Sun# LIBS = $(SUN4LIBS) -L/usr/lib -lXmu -lm -lX11

#HP# PLAT_FLAGS = -I/usr/include/X11R4
#HP# LIBS = -L/usr/lib/X11R4 -lXmu -lX11

#Apollo# PLAT_FLAGS =
#Apollo# LIBS = -lrpclib

#Dec# PLAT_FLAGS =
#Dec# LIBS = -lXmu -lX11

#Ibm# PLAT_FLAGS =
#Ibm# LIBS = -lXmu -lX11

# If You have X11R4 libraries uncomment the following line.
# X11R4_LIBS = -DHAVE_X11R4
CFLAGS = $(X11R4_LIBS) $(PLAT_FLAGS)

# 300007 is not an official RPC program number but will do for this demo. 
RPC_NUMBER = 300007



######################################################################
# The rest of this Makefile should not need configuring by the user. #
# Exception being, for 3.9 version of rpcgen remove line:            #
# "sh ../4.0hack stdfm_rpc.x".                                       #
######################################################################

SOURCE = ../stdfm_rpc.x
HEADERS = ../fm_commands.h
TOOLS = ../4.0hack
HELPDIR = $(FMHOME)/.fminit2.0/english/helpdir
DOCS = $(HELPDIR)/xrected.doc $(HELPDIR)/xrectedO.doc $(HELPDIR)/xrectedS.doc

OBJECTS = xdr.o

$(OBJECTS): stdfm_rpc.h

stdfm_rpc.h: stdfm_rpc.x
	sh ../4.0hack stdfm_rpc.x
	rpcgen -h -o stdfm_rpc.h stdfm_rpc.x

xdr.c: stdfm_rpc.h
	rpcgen -c -o xdr.c stdfm_rpc.x

fm_commands.h:
	cp ../fm_commands.h ./fm_commands.h

stdfm_rpc.x:
	cp ../stdfm_rpc.x ./stdfm_rpc.x

clean:
	rm -f *.o xdr.c stdfm_rpc.[xh] fm_commands.h
