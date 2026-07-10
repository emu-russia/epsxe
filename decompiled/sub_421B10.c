#include "pch.h"
bool __cdecl sub_421B10(__int16 a1)
{
  bool result; // al

  if ( (a1 & 2) != 0 )
  {
    result = (a1 & 0x2000) != 0;
    byte_516560[0] = result;
  }
  else
  {
    byte_5165A3 = 0;
    byte_516560[2] = 0;
    byte_516560[0] = 0x80;
    return 0;
  }
  return result;
}
