#ifndef __BUS_H__
#define __BUS_H__

/*
 * Declarations used for the Bus example in the Tools.h++ manual
 *
 * $Id: bus.h,v 7.2 1995/09/06 21:31:18 jims Exp $
 *
 * Copyright (c) 1989-1999 Rogue Wave Software, Inc.  All Rights Reserved.
 *
 * This computer software is owned by Rogue Wave Software, Inc. and is
 * protected by U.S. copyright laws and other laws and by international
 * treaties.  This computer software is furnished by Rogue Wave Software,
 * Inc. pursuant to a written license agreement and may be used, copied,
 * transmitted, and stored only in accordance with the terms of such
 * license and with the inclusion of the above copyright notice.  This
 * computer software or any other copies thereof may not be provided or
 * otherwise made available to any other person.
 *
 * U.S. Government Restricted Rights.  This computer software is provided
 * with Restricted Rights.  Use, duplication, or disclosure by the
 * Government is subject to restrictions as set forth in subparagraph (c)
 * (1) (ii) of The Rights in Technical Data and Computer Software clause
 * at DFARS 252.227-7013 or subparagraphs (c) (1) and (2) of the
 * Commercial Computer Software – Restricted Rights at 48 CFR 52.227-19,
 * as applicable.  Manufacturer is Rogue Wave Software, Inc., 5500
 * Flatiron Parkway, Boulder, Colorado 80301 USA.
 *
 ***************************************************************************
 *
 * $Log: bus.h,v $
 * Revision 7.2  1995/09/06 21:31:18  jims
 * Use new copyright macro
 *
 * Revision 7.1  1994/10/16  04:11:01  josh
 * Merged 6.1 and 7.0 development trees
 *
 * Revision 6.2  1994/07/12  20:40:30  vriezen
 * Updated Copyright
 *
 * Revision 6.1  1994/04/15  19:08:19  vriezen
 * Move all files to 6.1
 *
 * Revision 2.5  1993/06/21  18:00:55  keffer
 * Added RCS keywords
 *
 *
 */

#include "rw/rwset.h"
#include "rw/cstring.h"
#include "rw/collstr.h"

class Bus : public RWCollectable
{

	RWDECLARE_COLLECTABLE(Bus)

public:

	Bus();
	Bus(int busno, const RWCString& driver);
	~Bus();

	// Inherited from class "RWCollectable":
	RWspace		binaryStoreSize() const;
	int		compareTo(const RWCollectable*) const;
	RWBoolean	isEqual(const RWCollectable*) const;
	unsigned	hash() const;
	void		restoreGuts(RWFile&);
	void		restoreGuts(RWvistream&);
	void		saveGuts(RWFile&) const;
	void		saveGuts(RWvostream&) const;

	void		addPassenger(const char* name);
	void		addCustomer(const char* name);
	size_t		customers() const;
	size_t		passengers() const;
	RWCString	driver() const		{return driver_;}
	int		number() const		{return busNumber_;}

private:

	RWSet		customers_;
	RWSet*		passengers_;
	int		busNumber_;
	RWCString	driver_;
};

#endif

