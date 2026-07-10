#include "pch.h"
unsigned int sub_41ED00()
{
  unsigned int v0; // eax
  unsigned int result; // eax

  v0 = dword_50C2A4;
  if ( (dword_50C2A4 & 1) != 0 )
    v0 = dword_50C2A4 | 4;
  result = ((unsigned __int8)v0 ^ (unsigned __int8)(v0 >> 2)) & 0xF ^ v0;
  dword_50C2A4 = result;
  return result;
}
