#include "pch.h"
int __cdecl sub_436AF0(char *Buffer)
{
  int v2; // [esp+0h] [ebp-8h] BYREF
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_436910();
  sub_436960(aSystemCnf1, &v2, &v3);
  if ( v2 )
    return sub_436A00(v2, v3, Buffer, (int)&v3, (int)&Buffer);
  else
    return sprintf(Buffer, aSlus99999);
}
