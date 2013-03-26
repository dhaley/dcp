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
#include <rw/tvdlist.h>
#include <iostream.h>
#include <string.h>

class Dog {
  char* name;
public:
  Dog( const char* c = "") {
	name = new char[strlen(c)+1];
	strcpy(name, c); }

  ~Dog() { delete name; }

  // Define a copy constructor:
  Dog(const Dog& dog) {
	name = new char[strlen(dog.name)+1];
	strcpy(name, dog.name); }

  // Define an assignment operator:
  void operator=(const Dog& dog) {
	if (this!=&dog) {
	  delete name;
	  name = new char[strlen(dog.name)+1];
	  strcpy(name, dog.name);
	}
  }

  // Define an equality test operator:
  int operator==(const Dog& dog) const {
	return strcmp(name, dog.name)==0; }

  // order alphabetically:
  int operator<(const Dog& dog) const {
	return strcmp(name, dog.name) < 0; }

  friend ostream& operator<<(ostream& str, const Dog& dog){
    str << dog.name;
    return str;}
};

main(){
  RWTValDlist<Dog> terriers;
  terriers.insert("Cairn Terrier");  // NB: type conversion occurs
  terriers.insert("Irish Terrier");
  terriers.insert("Schnauzer");

  cout << "The list " <<
    (terriers.contains("Schnauzer") ? "does " : "does not ") <<
    "contain a Schnauzer\n";

  terriers.insertAt(
      terriers.index("Irish Terrier"),
      "Fox Terrier"
    );

  while (!terriers.isEmpty())
    cout << terriers.get() << endl;

  return 0;
}
