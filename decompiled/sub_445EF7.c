#include "pch.h"
_DWORD *__cdecl sub_445EF7(unsigned int a1)
{
  int v1; // edx
  _DWORD *result; // eax

  v1 = 0;
  dword_4FFA14 = a1;
  result = &unk_45B050;
  do
  {
    if ( a1 == *result )
    {
      result = (_DWORD *)dword_45B054[2 * v1];
      dword_4FFA10 = (int)result;
      return result;
    }
    result += 2;
    ++v1;
  }
  while ( result < dword_45B1B8 );
  if ( a1 < 0x13 || a1 > 0x24 )
  {
    if ( a1 < 0xBC || (dword_4FFA10 = 8, a1 > 0xCA) )
      dword_4FFA10 = 22;
  }
  else
  {
    dword_4FFA10 = 13;
  }
  return result;
}
