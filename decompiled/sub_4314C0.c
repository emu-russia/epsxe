#include "pch.h"
unsigned int __cdecl sub_4314C0(__int16 a1, _BYTE *a2, _BYTE *a3, _BYTE *a4)
{
  unsigned int result; // eax
  unsigned int v5; // eax
  unsigned int v6; // et2
  int v7; // [esp+0h] [ebp-4h] BYREF

  result = (unsigned __int8)dword_4FD9BC;
  v7 = 0;
  if ( a1 <= (int)(unsigned __int8)dword_4FD9BC )
  {
    if ( a1 )
      sub_431110(&v7, 8 * a1 + 5262496);
    else
      sub_431110(&v7, 8 * (unsigned __int8)dword_4FD9BC + 5262504);
    v5 = (v7 + 150) / 0x4Bu;
    *a4 = (v7 + 150) % 0x4Bu;
    v6 = v5 % 0x3C;
    result = v5 / 0x3C;
    *a3 = v6;
    *a2 = result;
  }
  return result;
}
