

#include <cstring>
#include <cstdlib> // for exit()
#include "labels.h"

Labels::Labels() : count(0)
{
} // Labels()


int Labels::find(const char* label) const
{
  for(int i = 0; i < count; i++)
    if(strcmp(addresses[i].getInfo(), label) == 0)
      return addresses[i].getAddress();

  cerr << label << " not found!\n";
  exit(1);  // should never get here!!

} // find()


istream& operator>> (istream &is, Labels &labels)
{
  char line[256], *ptr;
  int address = 100;
  labels.count = 0;

  while(is.getline(line, 256))
  {
    for(ptr = strchr(line, '\t'); ptr; ptr = strchr(line, '\t'))
      *ptr = ' ';  // replace all tabs with space characters

    for(ptr = line; *ptr == ' '; ptr++);  // get past leading spaces

    if(*ptr != '.' && *ptr != '_' && !strchr(ptr, ':'))
      address += 4;
    else // not a directive, nor a function label
      if (strchr(ptr, ':')) 
      {
        labels.addresses[labels.count].setAddress(address);
        *(strchr(ptr, ':')) = '\0';  // eliminate the colon from the label
        labels.addresses[labels.count++].setInfo(ptr);
    }  // if a directive
  }  // while more in file

  return is;
}  // operator>>
