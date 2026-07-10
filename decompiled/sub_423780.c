#include "pch.h"
int __cdecl sub_423780(const char *a1, int a2)
{
  char Buffer[3]; // [esp+4h] [ebp-10h] BYREF
  int v4; // [esp+7h] [ebp-Dh]

  sprintf(Buffer, "%s", a1);
  v4 = 65640;
  sub_438F70(a2, (int)Buffer, 7);
  sub_438F70(a2, (int)&dword_5164D0, 4);
  sub_438F70(a2, (int)&dword_566964, 4);
  sub_438F70(a2, (int)dword_5164E0, 96);
  return sub_438F70(a2, (int)byte_516600, 0x10000);
}
