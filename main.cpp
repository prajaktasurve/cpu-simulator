
#include <fstream>
#include <iomanip>
#include <iostream>
#include "registers.h"
#include "decoder.h"
#include "instruction.h"
#include "labels.h"
#include "memory.h"
#include "data.h"

using namespace std;


int main(int argc, char* argv[])
{
  Decoder decoder;
  Registers registers;
  Labels labels;
  Memory memory;
  

  Data* data1 = new Data(1000); 
  *data1 = 0;
  memory.insert(data1);

  Data* data2 = new Data(992); 
  *data2 = 0;
  memory.insert(data2);


  ifstream inf(argv[1]);
  inf >> memory;
  inf.clear();
  inf.seekg(0);
  inf >> labels;
  registers.set(Registers::eip, labels.find("main"));

  while(registers.get(Registers::eip) != 0)
  {
    const Instruction& instruction = memory.fetch(&registers);
    decoder.parse(instruction, &registers, memory, labels);
    decoder.execute(instruction, &registers, memory);
    cout << left << setw(20) << instruction << registers;
  } // while eip not zero

  return 0;
}  // main()

