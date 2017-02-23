CPU.out : main.o decoder.o memory.o instruction.o labels.o instruction2.o registers.o data.o word.o 
  g++ -ansi -Wall -g -o CPU.out main.o decoder.o memory.o instruction.o labels.o instruction2.o registers.o data.o word.o 
  
main.o : main.cpp registers.h decoder.h instruction.h labels.h memory.h
  g++ -ansi -Wall -g -c main.cpp

decoder.o : decoder.cpp decoder.h instruction.h registers.h memory.h
  g++ -ansi -Wall -g -c decoder.cpp

memory.o : memory.cpp memory.h word.h data.h registers.h
  g++ -ansi -Wall -g -c memory.cpp

instruction.o : instruction.cpp instruction.h 
  g++ -ansi -Wall -g -c instruction.cpp

labels.o : labels.cpp labels.h instruction2.h
  g++ -ansi -Wall -g -c labels.cpp

instruction2.o : instruction2.cpp instruction2.h 
  g++ -ansi -Wall -g -c instruction2.cpp

registers.o : registers.cpp registers.h memory.h
  g++ -ansi -Wall -g -c registers.cpp

data.o : data.cpp data.h word.h
  g++ -ansi -Wall -g -c data.cpp

word.o : word.cpp word.h
  g++ -ansi -Wall -g -c word.cpp

clean : 
  rm -f CPU.out main.o decoder.o memory.o instruction.o labels.o instruction2.o registers.o data.o word.o 
