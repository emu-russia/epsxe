#include "pch.h"
int __cdecl sub_43A0E0(int a1, unsigned int a2, unsigned int a3)
{
  int result; // eax
  _DWORD *v4; // edi
  int v5; // ebx

  result = 0;
  if ( !a1 )
    return -2;
  v4 = *(_DWORD **)(a1 + 28);
  if ( !v4 )
    return -2;
  v5 = a2;
  if ( a2 == -1 )
  {
    v5 = 6;
  }
  else if ( a2 > 9 )
  {
    return -2;
  }
  if ( a3 > 2 )
    return -2;
  if ( funcs_43A344[3 * v4[31]] != funcs_43A344[3 * v5] && *(_DWORD *)(a1 + 8) )
    result = sub_43A1B0(a1, 1);
  if ( v4[31] != v5 )
  {
    v4[31] = v5;
    v4[30] = (unsigned __int16)word_4487B2[6 * v5];
    v4[33] = (unsigned __int16)word_4487B0[6 * v5];
    v4[34] = (unsigned __int16)word_4487B4[6 * v5];
    v4[29] = (unsigned __int16)word_4487B6[6 * v5];
  }
  v4[32] = a3;
  return result;
}
