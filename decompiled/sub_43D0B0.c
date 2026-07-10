#include "pch.h"
int __cdecl sub_43D0B0(_WORD *a1, int a2, int a3)
{
  __int16 v3; // ax
  _BYTE *v4; // ecx
  int v5; // esi
  __int16 v6; // di
  int result; // eax
  int v9; // edi
  int v10; // ecx
  unsigned __int16 v11; // dx
  _BYTE v13[30]; // [esp+Ah] [ebp-1Eh] BYREF

  v3 = 0;
  v4 = v13;
  v5 = 15;
  do
  {
    v6 = *(_WORD *)&v4[a3 - (_DWORD)v13];
    v4 += 2;
    v3 = 2 * (v3 + v6);
    --v5;
    *((_WORD *)v4 - 1) = v3;
  }
  while ( v5 );
  result = a2;
  if ( a2 >= 0 )
  {
    v9 = a2 + 1;
    do
    {
      v10 = (unsigned __int16)a1[1];
      if ( (_WORD)v10 )
      {
        v11 = *(_WORD *)&v13[2 * v10 - 2];
        *(_WORD *)&v13[2 * v10 - 2] = v11 + 1;
        result = sub_43DFF0(v11, v10);
        *a1 = result;
      }
      a1 += 2;
      --v9;
    }
    while ( v9 );
  }
  return result;
}
