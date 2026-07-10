#include "pch.h"
char __cdecl sub_433220(unsigned int a1, char a2)
{
  char v2; // bl
  unsigned __int8 v4; // [esp+8h] [ebp-4h]

  v4 = 0;
  if ( !(_BYTE)dword_4FD9BC )
    return 0;
  v2 = a1;
  while ( 1 )
  {
    sub_431110(&a1, 8 * v4 + 5262504);
    a1 += 150;
    if ( (unsigned __int8)(a1 / 0x4B / 0x3C) == v2 && a1 / 0x4B % 0x3C == a2 )
      break;
    if ( ++v4 >= (unsigned __int8)dword_4FD9BC )
      return 0;
  }
  return a1 % 0x4B;
}
