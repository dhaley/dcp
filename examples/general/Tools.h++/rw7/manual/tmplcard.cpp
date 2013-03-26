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
/* Note: This example requires the C++ Standard Library */

#ifdef RW_NO_STL
#error This example is for users with access to the C++ Standard Library
#else

#include <iostream.h>
#include <algorithm>
#include <rw/tvordvec.h>
#include <stdcomp.h>

#ifndef RWSTD_NO_NAMESPACE
   using namespace std;
#endif

//MSVC 6.0 requires this separate declaration of Card and the << operator 
//struct Card;
//ostream& operator<<(ostream& ostr, const Card& c);

struct Card {
  char  rank;
  char  suit;

  bool operator== (const Card& c) const
    { return rank == c.rank && suit == c.suit; }

  bool operator< (const Card& c) const
    { return rank < c.rank; }

  Card() { }
  Card(char r, char s) : rank(r), suit(s) { }

  // print a card: '3-H' = three of hearts, 'A-S' = ace of spades
friend ostream& operator<<(ostream& ostr, const Card& c)
  { return (ostr << c.rank << "-" << c.suit << "  "); }
};

/*
 * A generator class - return Cards in sequence
 */
class DeckGen {
  int rankIdx;  // indexes into static arrays below
  int suitIdx;
  static const char Ranks[13];
  static const char Suits[4];
public:
  DeckGen() : rankIdx(-1), suitIdx(-1) { }

  // generate the next Card
  Card operator()()
    {
      rankIdx = (rankIdx + 1) % 13;
      if (rankIdx == 0)
	// cycled through ranks, move on to next suit:
	suitIdx = (suitIdx + 1) % 4;
      return Card(Ranks[rankIdx], Suits[suitIdx]);
    }
};

const char DeckGen::Suits[4]  = {'S', 'H', 'D', 'C' };
const char DeckGen::Ranks[13] = {'A', '2', '3', '4',
				 '5', '6', '7', '8',
				 '9', 'T', 'J', 'Q', 'K' };

int main(){
  // Tools.h++ collection:
  RWTValOrderedVector<Card> deck;
  RWTValOrderedVector<Card>::size_type pos;

  Card aceOfSpades('A','S');
  Card firstCard;

  // Use standard library algorithm to generate deck:
  generate_n(back_inserter(deck.std()), 52, DeckGen());
  cout << endl << "The deck has been created" << endl;

  // Use Tools.h++ member function to find card:
  pos = deck.index(aceOfSpades);
  cout << "The Ace of Spades is at position " << pos+1 << endl;

  // Use standard library algorithm to shuffle deck:
  random_shuffle(deck.begin(), deck.end());
  cout << endl << "The deck has been shuffled" << endl;

  // Use Tools.h++ member functions:
  pos = deck.index(aceOfSpades);
  firstCard = deck.first();

  cout << "Now the Ace of Spades is at position " << pos+1
    << endl << "and the first card is " << firstCard << endl;

  return 0;
}


/* Output:

The deck has been created
The Ace of Spades is at position 1

The deck has been shuffled
Now the Ace of Spades is at position 37
and the first card is Q-D  

*/

#endif  //#ifdef RW_NO_STL
