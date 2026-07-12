#include "pch.h"
char sub_42CE40()
{
  char result; // al

  result = byte_50AF07[69];
  if ( byte_50AF07[69] == 1 )
  {
    byte_50AF07[68] = 1;
    byte_50AF07[69] = 0;
    return 0;
  }
  else if ( byte_50AF07[69] )
  {
    return --byte_50AF07[69];
  }
  return result;
}
