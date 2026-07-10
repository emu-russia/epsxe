#include "pch.h"
BOOL __cdecl sub_43DA80(_DWORD *a1, int a2, int a3)
{
  unsigned int v3; // esi
  int v4; // ecx

  *(_WORD *)(a1[1447] + 2 * a1[1446]) = a2;
  *(_BYTE *)(a1[1444] + a1[1446]++) = a3;
  if ( a2 )
  {
    v3 = a2 - 1;
    ++a1[1450];
    ++LOWORD(a1[(unsigned __int8)byte_4494B8[a3] + 292]);
    if ( (unsigned int)(a2 - 1) >= 0x100 )
      v4 = (unsigned __int8)byte_4493B8[v3 >> 7];
    else
      v4 = (unsigned __int8)byte_4492B8[v3];
    ++LOWORD(a1[v4 + 608]);
  }
  else
  {
    ++LOWORD(a1[a3 + 35]);
  }
  return a1[1446] == a1[1445] - 1;
}
