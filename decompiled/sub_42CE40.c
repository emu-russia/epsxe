#include "pch.h"
char sub_42CE40()
{
  char result; // al

  result = byte_50AF4C;
  if ( byte_50AF4C == 1 )
  {
    byte_50AF4B = 1;
    byte_50AF4C = 0;
    return 0;
  }
  else if ( byte_50AF4C )
  {
    return --byte_50AF4C;
  }
  return result;
}
