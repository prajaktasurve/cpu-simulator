#include "data.h"
#include "word.h"

Data::Data(int a) : Word(a)
{
} // constructor

int& Data::get()
{
  return num;
} // get()

const int& Data::get() const
{
  return num;
} // get () const

void Data::operator= (int n)
{
  num = n;
} // assignment operator