#include "pch.h"
int __cdecl hw_reg_freeze(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 65640;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  gzwrite(a2, (unsigned __int8 *)dword_5164D0, 4u);
  gzwrite(a2, (unsigned __int8 *)dword_566964, 4u);
  gzwrite(a2, (unsigned __int8 *)dword_5164E0, 0x60u);
  return gzwrite(a2, (unsigned __int8 *)byte_516600, 0x10000u);
}
