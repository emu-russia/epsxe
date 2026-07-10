#include "pch.h"
int __cdecl sub_40CDA0(__int16 a1)
{
  int v1; // eax
  int result; // eax

  v1 = dword_4F7554;
  *(_WORD *)((char *)spu_ram + dword_4F7554) = a1;
  result = (v1 + 2) & 0x7FFFF;
  dword_4F7554 = result;
  return result;
}
