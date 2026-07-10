#include "pch.h"
char sub_421B40()
{
  unsigned int i; // eax

  byte_516560[0] = 0;
  byte_5165A3 = 0;
  byte_516560[2] = 0;
  byte_516560[1] = 0;
  for ( i = 3; i < 6; ++i )
  {
    byte_516560[i + 3] = -1;
    byte_5165A4[i] = -1;
  }
  byte_516560[3] = 0;
  byte_516564[0] = 65;
  byte_516565[0] = 90;
  byte_5165A4[0] = 0;
  byte_5165A5 = 65;
  byte_5165A6 = 90;
  return 90;
}
