/*
 * This example is from the Tools.h++ manual, version 7
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
 */
//Instructions:  compile as a Windows program.
//               Run clipbuff, then using your favorite text editor or word
//               processor, select paste and see the result!

#include <rw/winstrea.h>

#include <stdlib.h>
#include <iostream.h>
#include <windows.h>


void postToClipboard(HWND owner);

main()
{
   postToClipboard(NULL);

   cout << "A message has been posted to the clipboard." << endl
        << "Open an editor and select paste to view it! " << endl;

   return 0;
}


// PASS YOUR WINDOW HANDLE TO THIS FUNCTION THEN PASS YOUR VALUES
// TO THE CLIPBOARD USING ostr.

void postToClipboard(HWND owner)
{
   //Build the clipstream buffer on the heap
   RWCLIPstreambuf* buf = new
   RWCLIPstreambuf();

   ostream ostr(buf);

   double d = 12.34;

   ostr << "Some text to be exchanged through the clipboard." << endl;
   ostr << "Might as well add a double: " << d << endl;
   ostr.put('\0');		// Include the terminating null

   // Lock the streambuf, get its handle:
   HANDLE hMem = buf->str();

   OpenClipboard(owner);

   EmptyClipboard();
   SetClipboardData(CF_TEXT, hMem);
   CloseClipboard();
 
   // Don't delete the buffer!.  Windows is now responsible for it.
}
