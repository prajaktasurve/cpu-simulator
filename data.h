#ifndef DATA_H
#define DATA_H
#include "word.h"

class Data : public Word
{
  int num;

  public:
  Data(int a);
  int& get();
  const int& get() const;
  void operator= (int n);

}; // class Data;



#endif  // DATA_H 