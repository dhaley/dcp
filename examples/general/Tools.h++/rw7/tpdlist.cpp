/*
 * RWTPtrDlist<T> example, from the manual.
 *
 * $Id: tpdlist.cpp,v 7.9 1996/08/07 05:21:24 hart Exp $
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
 * $Log: tpdlist.cpp,v $
 *
 */

#include "rw/compiler.h"

#ifdef RW_NO_TEMPLATES
#error "Your compiler does not support templates."
#error "You cannot compile this example."
#else

#include "rw/tpdlist.h"
#include "rw/rstream.h"
#include "dog.h"


int main()
{
  /*                                                                                
   * If we're using the Standard C++ Library and the iostream operators             
   * are in the std namespace, we need to pull in namespace std, or                 
   * scope the operator with std::.                                                 
   */                                                                               
#if !defined(RW_NO_STL) && !defined(RW_NO_STD_NAMESPACE) && !defined(RW_NO_IOSTD)   
  using namespace std;                                                              
#endif
  /*
   *  borland 4 needs the std namespace
   */
#if defined(RW_BCB_NAMESPACE) 
  using namespace std;
#endif
  RWTPtrDlist<Dog> terriers;
  terriers.insert(new Dog("Cairn Terrier"));
  terriers.insert(new Dog("Irish Terrier"));
  terriers.insert(new Dog("Schnauzer"));

  Dog key1("Schnauzer");
  cout << "The list " <<
    (terriers.contains(&key1) ? "does " : "does not ") <<
    "contain a Schnauzer\n";

  Dog key2("Irish Terrier");
  terriers.insertAt(
      terriers.index(&key2),
      new Dog("Fox Terrier")
    );

  Dog* d;
  while (!terriers.isEmpty()) {
    d = terriers.get();
    cout << *d << endl;
    delete d;
  }

  return 0;
}

#endif  /* RW_NO_TEMPLATES */

