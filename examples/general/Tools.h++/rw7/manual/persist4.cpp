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
#include <iostream.h>   // For user output only.
#include <assert.h>
#include <rw/cstring.h>
#include <rw/rwfile.h>
#include <rw/epersist.h>

//------------------ Declarations ---------------------

//------------------- Developer -----------------------

class Developer {
  public:
    Developer(const char* name = "", Developer* anAlias = rwnil)
      : name_(name), alias_(anAlias) {}

  RWCString         name_;
  Developer*        alias_;
};

#include <rw/edefs.h>
RWDECLARE_PERSISTABLE(Developer)

//--------------------- Team --------------------------

class Team {
  public:
    Developer*  member_[3];
};

RWDECLARE_PERSISTABLE(Team);

//---------- rwSaveGuts and rwRestoreGuts -------------

//------------------- Developer -----------------------

RWDEFINE_PERSISTABLE(Developer)
// This macro generates the following insertion and extraction
// operators:
//    RWvostream& operator<<
//      (RWvostream& strm, const Developer& item)
//    RWvistream& operator>>(RWvistream& strm, Developer& obj)
//    RWvistream& operator>>(RWvistream& strm, Developer*& pObj)
//    RWFile& operator<<(RWFile& strm, const Developer& item)
//    RWFile& operator>>(RWFile& strm, Developer& obj)
//    RWFile& operator>>(RWFile& strm, Developer*& pObj)

void rwSaveGuts(RWFile& file, const Developer& developer){
// Called by:
//    RWFile& operator<<(RWFile& strm, const Developer& item)

  file << developer.name_;        // Save name.

  // See if alias_ is pointing to a Developer in memory.  
  // If not, then rwSaveGuts stores a boolean false to signify
  // that alias_ is a nil pointer. 
  // If alias_ is pointing to a Developer, 
  // then rwSaveGuts stores a boolean true 
  // and stores the value of the Developer 
  // that alias_ is pointing to.  

  if (developer.alias_ == rwnil) 
    file << FALSE;                // No alias.
  else {
    file << TRUE;
    file << *(developer.alias_);  // Save alias.
  }
}

void rwSaveGuts(RWvostream& stream, const Developer& developer) {
// Called by:
//    RWvostream& operator<<
//      (RWvostream& strm, const Developer& item)

  stream << developer.name_;        // Save name.

  // See if alias_ is pointing to a Developer in memory.  

  if (developer.alias_ == rwnil)
    stream << FALSE;                // No alias.
  else {
    stream << TRUE;
    stream << *(developer.alias_);  // Save alias.
  }
}

void rwRestoreGuts(RWFile& file, Developer& developer) {
//  Called by:
//    RWFile& operator>>(RWFile& strm, Developer& obj)

  file >> developer.name_;        // Restore name.

  // Should developer.alias_ point to a Developer?

  RWBoolean alias;
  file >> alias;

  // If alias_ should point to a Developer, 
  // then rwRestoreGuts restores the Developer object 
  // and then updates alias_ to point to the new Developer.

  if (alias)                     // Yes.
     file >> developer.alias_;
        // Call:
        //    RWFile& operator>>(RWFile& strm, Developer*& pObj)
}

void rwRestoreGuts(RWvistream& stream, Developer& developer) {
// Called by:
//   RWvistream& operator>>(RWvistream& strm, Developer& obj)

  stream >> developer.name_;     // Restore name.

  // Should developer.alias_ point to a Developer?

  RWBoolean alias;
  stream.get(alias);

  if (alias)                    // Yes.
    stream >> developer.alias_;  
       // Restore alias and update pointer. 
       // Calls:
       //    RWvistream& operator>>
       //      (RWvistream& strm, Developer*& pObj)

}

// For user output only:

ostream& operator<<(ostream& stream, const Developer& d) {
  stream << d.name_
    << " at memory address: " << (void*)&d;

  if (d.alias_)
    stream << " has an alias at memory address: " 
      << (void*)d.alias_ << " ";
  else
    stream << " has no alias.";

  return stream;
}


//--------------------- Team -------------------------------

RWDEFINE_PERSISTABLE(Team);
// This macro generates the following insertion and extraction
// operators:
//    RWvostream& operator<<
//      (RWvostream& strm, const Team& item)
//    RWvistream& operator>>(RWvistream& strm, Team& obj)
//    RWvistream& operator>>(RWvistream& strm, Team*& pObj)
//    RWFile& operator<<(RWFile& strm, const Team& item)
//    RWFile& operator>>(RWFile& strm, Team& obj)
//    RWFile& operator>>(RWFile& strm, Team*& pObj)


void rwSaveGuts(RWFile& file, const Team& team){
// Called by RWFile& operator<<(RWFile& strm, const Team& item)

  for (int i = 0; i < 3; i++)
    file << *(team.member_[i]);    
      // Save Developer value.
      // Call:
      //   RWFile& operator<<
      //     (RWFile& strm, const Developer& item)
}

void rwSaveGuts(RWvostream& stream, const Team& team) {
// Called by:
//    RWvostream& operator<<(RWvostream& strm, const Team& item)

  for (int i = 0; i < 3; i++)
    stream << *(team.member_[i]);
      // Save Developer value.
      // Call:
      //   RWvostream& operator<<
      //     (RWvostream& strm, const Developer& item)

}

void rwRestoreGuts(RWFile& file, Team& team) {
// Called by RWFile& operator>>(RWFile& strm, Team& obj)

  for (int i = 0; i < 3; i++)
    file >> team.member_[i];   
      // Restore Developer and update pointer.
      // Call:
      //    RWFile& operator>>(RWFile& strm, Developer*& pObj)
}

void rwRestoreGuts(RWvistream& stream, Team& team) {
// Called by:
//    RWvistream& operator>>(RWvistream& strm, Team& obj)

  for (int i = 0; i < 3; i++)
    stream >> team.member_[i]; 
       // Restore Developer and update pointer.
       // Call:
       //    RWvistream& operator>>
       //      (RWvistream& strm, Developer*& pObj)
}

// For user output only:

ostream& operator<<(ostream& stream, const Team& t) {
  for (int i = 0; i < 3; i++)
    stream << "[" << i << "]:" << *(t.member_[i]) << endl;
  return stream;
}

//-------------------- main --------------------------

main (){
  Developer*  kevin   = new Developer("Kevin");
  Developer*  rudi    = new Developer("Rudi", kevin);
  Team        team1;

  team1.member_[0] = rudi;
  team1.member_[1] = rudi;
  team1.member_[2] = kevin;

  cout << "team1 (before save):" << endl
    << team1 << endl << endl;   // Output to user.
  {
    RWFile    f("team.dat");
    f << team1;  // Isomorphic persistence of team.
  }

  Team        team2;
  {
    RWFile            f("team.dat");
    f >> team2;
  }
  cout << "team2 (after restore):" << endl
    << team2 << endl << endl;   // Output to user.
  
  delete kevin;
  delete rudi;
  return 0;
}
