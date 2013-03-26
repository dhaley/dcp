#pragma ident   "@(#)vehicle_list.cc	1.7    02/02/05 SMI"

// Copyright 1991, 1994, 2000, 2002 Sun Microsystems, Inc.  All Rights Reserved

#include "vehicle_list.h"


List* List::prev(Vehicle *veh)
{
  List *i = this->find(veh);

  if (i->hasValue()) return i->p;
  else               return NULL;    // couldn't find vehicle
}


List* List::next(Vehicle *veh)
{
  List *i = this->find(veh);

  if (i->hasValue()) return i->n;
  else               return NULL;    // couldn't find vehicle
}


List* List::find(Vehicle *veh)
{
  for (List *i = this->first(); i->hasValue(); i = i->n) 
    {
      if (i->v->name() == veh->name()) 
	{
	  return i;
	}
    }
  return NULL; // couldn't find vehicle
}


void List::remove(Vehicle *veh)
{
  List *i = this->find(veh);

  if (i->hasValue())
    {
      i->p->n = i->n;
      i->n->p = i->p;
   // delete i;
    }
}


void List::append(Vehicle *veh)
{
  List *i = new List();
  
  i->v = veh;
  i->n = this;
  i->p = p;
  p->n = i;
  p    = i;
}


void List::prepend(Vehicle *veh)
{
  List *i = new List();

  i->v = veh;
  i->p = this;
  i->n = n;
  n->p = i;
  n    = i;
}


void List::insert(Vehicle *veh)
{
  //
  // Scan over list looking for element which is smaller than v and then insert v after it.
  //
  for (List *i = this->last(); i->hasValue(); i = i->p) 
    {
      if (i->v->pos() < veh->pos())
	{
	  i->insertAfter(veh);
	  return;
	}
    }
  //
  // If there is no element smaller than v, insert it at the beginning.
  //
  this->insertAfter(veh);
}


ostream& operator<< (ostream & o, List & l)
{ 
  o << "{ ";

  for (List *i = l.first(); i->hasValue(); i = i->next())
    {
      o << i->value();
      if (i != l.last()) o << " , ";
    }

  o << " }" << endl;

  return o;
}


#ifdef  TESTING

main()
{
  List *l = new List();

  cout << "is empty list? " << l->isEmpty() << " : " << *l << endl;

  l->insert(3);

  l->insert(1);

  l->insert(2);

  cout << "full list: " << *l << endl;

  l->remove(2);

  l->remove(1);

  cout << "should have 3: " << *l << endl;

  l->append(17);
  l->append(10);

  cout << "append 17 then 10: " << *l << endl;

  l->remove(17);

  l->remove(3);

  l->remove(10);

  l->remove(4);

  l->prepend(2);

  cout << *l << endl;
}


#endif

