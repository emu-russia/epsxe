#include "pch.h"
unsigned __int8 __cdecl sub_436AF0(char *Buffer)
{
  int v2; // [esp+0h] [ebp-8h] BYREF
  int v3; // [esp+4h] [ebp-4h] BYREF

  sub_436910();
  sub_436960("SYSTEM.CNF;1", &v2, (int **)&v3);
  if ( v2 )
    return sub_436A00(v2, v3, Buffer, &v3, (int **)&Buffer);
  else
    return sprintf(Buffer, "SLUS_999.99");
}
