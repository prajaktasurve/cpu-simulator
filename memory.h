#ifndef MEMORY_H
#define MEMORY_H
#include "word.h"
#include "data.h"
#include "instruction.h"
#include <fstream>

class Memory;
class Registers;

class ListNode
{
  Word* word;
  ListNode* next;
  ListNode(Word* w, ListNode* listnode);
  ~ListNode();
  friend class Memory;
}; // class ListNode; 


class Memory
{
  ListNode* head;
  public:
  Memory(); 
  ~Memory(); 
  Word& operator[] (int address);
  const Word& operator[] (int address) const;
  const Instruction& fetch(Registers *registers) const;
  friend ifstream& operator>> (ifstream &is, Memory& memory);
  void insert(Word* w);
}; // class Memory;



#endif  // MEMORY_H 