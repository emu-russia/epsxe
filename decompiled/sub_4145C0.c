#include "pch.h"
int sub_4145C0()
{
  int result; // eax
  int v1; // edx
  int v2; // ecx

  result = ((__int16)word_8A7F2C * unk_8A7F88 - (__int16)word_8A7F28 * unk_8A7F90) >> 12;
  v1 = (unk_8A7F90 * (__int16)word_8A7F24 - (__int16)word_8A7F2C * SLOWORD(unk_8A7F80[0])) >> 12;
  v2 = ((__int16)word_8A7F28 * SLOWORD(unk_8A7F80[0]) - unk_8A7F88 * (__int16)word_8A7F24) >> 12;
  unk_8A7F64 = result;
  unk_8A7F68 = v1;
  unk_8A7F6C = v2;
  if ( result >= -32768 )
  {
    if ( result <= 0x7FFF )
    {
      word_8A7F24 = ((__int16)word_8A7F2C * unk_8A7F88 - (__int16)word_8A7F28 * unk_8A7F90) >> 12;
    }
    else
    {
      unk_8A7FFC |= 0x81000000;
      word_8A7F24 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x81000000;
    word_8A7F24 = -32768;
  }
  if ( v1 >= -32768 )
  {
    if ( v1 <= 0x7FFF )
    {
      word_8A7F28 = v1;
    }
    else
    {
      unk_8A7FFC |= 0x80800000;
      word_8A7F28 = 0x7FFF;
    }
  }
  else
  {
    unk_8A7FFC |= 0x80800000;
    word_8A7F28 = -32768;
  }
  if ( v2 >= -32768 )
  {
    if ( v2 <= 0x7FFF )
    {
      word_8A7F2C = v2;
    }
    else
    {
      word_8A7F2C = 0x7FFF;
      result = unk_8A7FFC | 0x400000;
      unk_8A7FFC |= 0x400000u;
    }
  }
  else
  {
    word_8A7F2C = -32768;
    result = unk_8A7FFC | 0x400000;
    unk_8A7FFC |= 0x400000u;
  }
  return result;
}
