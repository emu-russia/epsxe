#include "pch.h"
int __cdecl sub_43D1A0(_WORD *a1, int a2, int a3)
{
  int result; // eax
  int v4; // ecx
  int v5; // edi
  int v6; // edx
  int v7; // esi
  unsigned __int16 *v8; // ebp
  int v9; // eax
  int v10; // [esp+Ch] [ebp-4h]
  int v11; // [esp+18h] [ebp+8h]

  result = a2;
  v4 = *(unsigned __int16 *)(a2 + 2);
  v5 = 0;
  v10 = -1;
  v6 = 7;
  v7 = 4;
  if ( !(_WORD)v4 )
  {
    v6 = 138;
    v7 = 3;
  }
  *(_WORD *)(a2 + 4 * a3 + 6) = -1;
  if ( a3 >= 0 )
  {
    v11 = a3 + 1;
    v8 = (unsigned __int16 *)(result + 6);
    do
    {
      v9 = v4;
      v4 = *v8;
      if ( ++v5 >= v6 || v9 != v4 )
      {
        if ( v5 >= v7 )
        {
          if ( v9 )
          {
            if ( v9 != v10 )
              ++a1[2 * v9 + 1338];
            ++a1[1370];
          }
          else if ( v5 > 10 )
          {
            ++a1[1374];
          }
          else
          {
            ++a1[1372];
          }
        }
        else
        {
          a1[2 * v9 + 1338] += v5;
        }
        v5 = 0;
        v10 = v9;
        if ( v4 )
        {
          if ( v9 == v4 )
          {
            v6 = 6;
            v7 = 3;
          }
          else
          {
            v6 = 7;
            v7 = 4;
          }
        }
        else
        {
          v6 = 138;
          v7 = 3;
        }
      }
      v8 += 2;
      result = --v11;
    }
    while ( v11 );
  }
  return result;
}
