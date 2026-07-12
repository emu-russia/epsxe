#include "pch.h"
char sub_42C9A0()
{
  char result; // al

  result = byte_50AF07[62];
  if ( !byte_50AF07[62] && (byte_50AF07[63] || (result = byte_50BF6A) != 0) )
  {
    result = ++word_4FD87C;
    if ( (unsigned __int16)word_4FD87C >= (unsigned __int16)word_455FA6 )
    {
      sub_42C8D0();
      result = 10;
      word_4FD87C = 0;
      if ( (unsigned __int16)word_455FA6 > 0xAu )
        word_455FA6 = 10;
    }
  }
  return result;
}
