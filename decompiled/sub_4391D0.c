#include "pch.h"
int __cdecl sub_4391D0(int a1, int Offset, int a3)
{
  int v3; // eax
  int v4; // ebx
  void *v5; // edi
  int v6; // eax
  int v7; // eax
  int v9; // edi
  int v10; // ecx
  unsigned int v11; // eax
  int v12; // eax
  int v13; // eax
  FILE *v14; // [esp-Ch] [ebp-18h]

  if ( a1 )
  {
    if ( a3 != 2 )
    {
      v3 = *(_DWORD *)(a1 + 56);
      if ( v3 != -1 && v3 != -3 )
      {
        if ( *(_BYTE *)(a1 + 92) == 119 )
        {
          v4 = Offset;
          if ( !a3 )
            v4 = Offset - *(_DWORD *)(a1 + 8);
          if ( v4 >= 0 )
          {
            if ( !*(_DWORD *)(a1 + 68) )
            {
              v5 = malloc(0x4000u);
              *(_DWORD *)(a1 + 68) = v5;
              memset(v5, 0, 0x4000u);
            }
            if ( v4 <= 0 )
              return *(_DWORD *)(a1 + 8);
            while ( 1 )
            {
              v6 = 0x4000;
              if ( v4 < 0x4000 )
                v6 = v4;
              v7 = sub_438F70(a1, *(_DWORD *)(a1 + 68), v6);
              if ( !v7 )
                break;
              v4 -= v7;
              if ( v4 <= 0 )
                return *(_DWORD *)(a1 + 8);
            }
          }
          return -1;
        }
        v9 = Offset;
        if ( a3 == 1 )
          v9 = *(_DWORD *)(a1 + 20) + Offset;
        if ( v9 >= 0 )
        {
          if ( *(_DWORD *)(a1 + 88) )
          {
            v10 = *(_DWORD *)(a1 + 68);
            v14 = *(FILE **)(a1 + 64);
            *(_DWORD *)(a1 + 4) = 0;
            *(_DWORD *)a1 = v10;
            if ( fseek(v14, v9, 0) >= 0 )
            {
              *(_DWORD *)(a1 + 20) = v9;
              *(_DWORD *)(a1 + 8) = v9;
              return v9;
            }
            return -1;
          }
          v11 = *(_DWORD *)(a1 + 20);
          if ( v9 < v11 )
          {
            if ( (int)sub_439320(a1) < 0 )
              return -1;
          }
          else
          {
            v9 -= v11;
          }
          if ( !v9 )
            return *(_DWORD *)(a1 + 20);
          if ( !*(_DWORD *)(a1 + 72) )
            *(_DWORD *)(a1 + 72) = malloc(0x4000u);
          if ( v9 <= 0 )
            return *(_DWORD *)(a1 + 20);
          while ( 1 )
          {
            v12 = 0x4000;
            if ( v9 < 0x4000 )
              v12 = v9;
            v13 = sub_438CA0(a1, *(char **)(a1 + 72), v12);
            if ( v13 <= 0 )
              break;
            v9 -= v13;
            if ( v9 <= 0 )
              return *(_DWORD *)(a1 + 20);
          }
        }
      }
    }
  }
  return -1;
}
