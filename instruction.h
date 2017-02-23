#ifndef INSTRUCTION_H
#define INSTRUCTION_H
#include <fstream>
#include "word.h"

using namespace std;

class Instruction : public Word
{
  char *info;
  public:
  Instruction(int a);
  ~Instruction();
  const char* getInfo() const;
  void operator= (const char* information);
  friend ostream& operator<< (ostream& os, const Instruction& ins);

}; //class Instruction

#endif  // INSTRUCTION_H 