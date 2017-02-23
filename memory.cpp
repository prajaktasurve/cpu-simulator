#include "memory.h"
#include "word.h"
#include "data.h"
#include "registers.h"
#include "instruction.h"
#include "memory.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

ListNode::ListNode(Word* w, ListNode* listnode)
{
  word = w;
  next = listnode;
} // listnode constructor
 
ListNode::~ListNode()
{
  delete word;
} //listnode destructor

Memory::Memory()
{
  head = NULL;
} //constructor

Memory::~Memory()
{
  ListNode *ptr;
  
  for (ptr = head; ptr; ptr = head)
  {
    head = ptr->next;
    delete ptr;
  } // deletes linked list
}  // destructor



Word& Memory::operator[] (int address)   
{
  ListNode* ptr;
  Data* d = new Data(address);

  for (ptr = head; ptr && ptr->next; ptr = ptr->next)
    if (!(*(ptr->word) < *d) && !(*d < *(ptr->word)))     //if equal
      return *(ptr->word);                                                
  insert(d);
  return *d;
} // [] operator 



const Word& Memory::operator[] (int address) const    
{
  ListNode* ptr;
  Word *w = new Word(address);                       //huh?
  for (ptr = head; ptr && ptr->next; ptr = ptr->next)
    if (!(*(ptr->word) < *w) && !(*w < *(ptr->word)))
          return *(ptr->word);
  if (!(*(ptr->word) < *w) && !(*w < *(ptr->word)))
    return *(ptr->word);
  cerr << "Seg fault at address: " << address << endl; 
  exit(1);
} // [] operator const




void Memory::insert(Word* w) //***
{
  ListNode *ptr, *prev; 
  prev = NULL;

  for (ptr = head; ptr && *(ptr->word) < *w; ptr = ptr->next)
    prev = ptr;

  if (prev)
    prev->next = new ListNode(w, ptr);  //insert in middle 
  else // prev == null
    head = new ListNode(w, ptr);
} //insert

const Instruction& Memory::fetch(Registers *registers) const 
{
  const Instruction &instruction = dynamic_cast <const Instruction&> 
                                   ((*this)[registers->get(Registers::eip)]);
  registers->set(Registers::eip, registers->get(Registers::eip) + 4);
  return instruction;
} // fetch()


ifstream& operator>> (ifstream &is, Memory& memory)               
{
  char line[256], *ptr;
  int address = 100;

  while(is.getline(line, 256))
  {
    for(ptr = strchr(line, '\t'); ptr; ptr = strchr(line, '\t'))
      *ptr = ' ';  // replace all tabs with space characters

    for(ptr = line; *ptr == ' '; ptr++);  // get past leading spaces

    if(!strchr(line, ':') && *ptr != '.' && *ptr != '_')
    {
      Instruction *i = new Instruction(address);
      (*i) = ptr;
      address += 4;
      memory.insert(i);
    } // if not directive, nor main:
  }  // while more in file

  return is;
}  // operator>>

