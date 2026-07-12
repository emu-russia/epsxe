#include "pch.h"
__int16 sub_42CA00()
{
  __int16 result; // ax

  byte_50BF65 = 1;
  word_50BF82 = 0;
  byte_50BF67 = 0;
  byte_50BF64 = 0;
  if ( country_setting == 1 )
    LOBYTE(result) = byte_50AF07[72] < 0 ? 104 : -48;
  else
    LOBYTE(result) = byte_50AF07[72] < 0 ? 104 : -47;
  byte_50BF68 = result;
  result = (unsigned __int8)result;
  word_50BF7E = result;
  word_50BF80 = (unsigned __int8)result;
  if ( !byte_50AF07[70] )
  {
    result = 3 * (unsigned __int8)result;
    word_50BF80 = result;
  }
  return result;
}
