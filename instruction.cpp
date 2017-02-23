#include "instruction.h"
#include "word.h"
#include <iostream>
#include <cstring>
#include <cstdlib>

using namespace std;

Instruction::Instruction(int a) : Word(a), info(NULL)
{
}  // Instruction()


Instruction::~Instruction()
{
  if(info)
    delete [] info;
}  // ~Instruction

const char* Instruction::getInfo() const
{
  return info;
} // get()

void Instruction::operator= (const char* information)
{
  info = new char[strlen(information) + 1];
  strcpy(info, information);
} // operator=


ostream& operator<< (ostream& os, const Instruction& ins)
{
  os << ins.info; //endl required? 
  return os;
} // operator<<