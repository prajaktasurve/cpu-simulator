#include "word.h"

Word::Word(int a)
{
  address = a;
} // Word() constructor

Word::~Word()
{
} // ~Word() destructor

bool Word::operator< (const Word& rhs) const
{
  return address < rhs.address;
} //operator< ()