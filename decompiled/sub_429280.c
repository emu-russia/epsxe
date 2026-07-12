#include "pch.h"
__int16 __cdecl sub_429280(unsigned int a1)
{
  __int16 result; // ax

  *(_DWORD *)dword_4FC4F0 = a1;
  if ( (a1 & 0xF5FF0000) == 0x30000000 )
    dword_4FC50C = (unsigned __int16)a1;
  result = (a1 >> 10) & 0x8000;
  word_4FC510 = result;
  return result;
}
