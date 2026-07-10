#include "pch.h"
int sub_4144A0()
{
  int result; // eax
  int v1; // ecx
  int v2; // edx

  result = (__int16)word_8A7F2C * word_8A7F88 - (__int16)word_8A7F28 * word_8A7F90;
  v1 = (__int16)word_8A7F28 * SLOWORD(word_8A7F80[0]) - word_8A7F88 * (__int16)word_8A7F24;
  v2 = word_8A7F90 * (__int16)word_8A7F24 - (__int16)word_8A7F2C * SLOWORD(word_8A7F80[0]);
  dword_8A7F64 = result;
  dword_8A7F68 = v2;
  dword_8A7F6C = v1;
  if ( result >= (int)-0x8000u )
  {
    if ( result <= 0x7FFF )
    {
      word_8A7F24 = (__int16)word_8A7F2C * word_8A7F88 - (__int16)word_8A7F28 * word_8A7F90;
    }
    else
    {
      dword_8A7FFC |= 0x81000000;
      word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x81000000;
    word_8A7F24 = -0x8000u;
  }
  if ( v2 >= (int)-0x8000u )
  {
    if ( v2 <= 0x7FFF )
    {
      word_8A7F28 = v2;
    }
    else
    {
      dword_8A7FFC |= 0x80800000;
      word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    dword_8A7FFC |= 0x80800000;
    word_8A7F28 = -0x8000u;
  }
  if ( v1 >= (int)-0x8000u )
  {
    if ( v1 <= 0x7FFF )
    {
      word_8A7F2C = v1;
    }
    else
    {
      word_8A7F2C = 0x7FFF;
      result = dword_8A7FFC | 0x400000;
      dword_8A7FFC |= 0x400000u;
    }
  }
  else
  {
    word_8A7F2C = -0x8000u;
    result = dword_8A7FFC | 0x400000;
    dword_8A7FFC |= 0x400000u;
  }
  return result;
}
