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
#include <iostream.h>
#include <fstream.h>
#include <rw/auditbuf.h>
#include <rw/pstream.h>
#include <rw/cstring.h>
void doCrc (unsigned char c, void* x) {
  *(unsigned char*)x ^= c;
}

int main() {
  { // just a block to control variable lifetime
    unsigned char check = '\0';

    // create an output stream
    ofstream                            op("crc.pst");

    // create an RWAuditStreamBuffer that will do CRC
    RWAuditStreamBuffer               crcb(op,doCrc,&check);

    // create an RWpostream to put the data through.
RWpostream                           p(&crcb);

    // now send some random stuff to the stream
    p << RWCString("The value of Tools.h++ is at least ");
    p << (int)4;
    p << RWCString(" times that of the next best library!\n") ;
    p << RWCString("Pi is about ") << (double)3.14159 << '.';

    // finally, save the sum on the stream itself.
p << (unsigned int)check; // alters check, _after_ saving it...

    // just for fun, print out some statistics:
    cout << "We just saved " << crcb 
		  << " bytes of data to the file." << endl;
    cout << "The checksum for those bytes was " <<check << endl;
} // end of block

  // now read the data back in, checking to see if it survived.
  unsigned char check = '\0';

  // create an instream
  ifstream                            ip("crc.pst");

  // create an RWAuditStreamBuffer that will do CRC
  RWAuditStreamBuffer               crcb(ip,doCrc,&check);

  // create an RWpistream to interpret the bytes
  RWpistream                           p(&crcb);

  RWCString first, mid1, mid2;
  int value;
  double pi;
  char pnc;
  unsigned int savedCRC;
  unsigned char matchCRC;
  // read in the data. Don\'t read the checksum yet!
  p >> first >> value >> mid1 >> mid2 >> pi >> pnc;
  // save the checksum
  matchCRC = check;
  // Now it is safe to alter the running checksum by reading in
  // the one saved in the file.
p >> savedCRC;

  if(savedCRC != matchCRC) {
    cout << "Checksum error. Saved CRC: " << savedCRC
         << " built CRC: " << matchCRC << dec << endl;
  }
  else {
    cout << "The message was: " << endl;
    cout << first << value << mid1 << mid2 << pi << pnc << endl;
  }
  // just for fun, print out some statistics:
  cout	<< "We just read " << crcb 
		<< " bytes of data from the file." << endl;
  cout	<< "The checksum was " << matchCRC << flush;
  cout	<< " and the saved checksum was " << savedCRC << endl;
return 0;
}
