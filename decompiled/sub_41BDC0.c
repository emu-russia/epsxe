#include "pch.h"
char __cdecl sub_41BDC0(const char *a1)
{
  char result; // al
  int *v2; // ebp
  int v3; // edi
  int v4; // ebp
  int v5; // esi
  char v6; // al
  bool v7; // zf
  int *v8; // [esp+0h] [ebp-8h]
  int v9; // [esp+4h] [ebp-4h]

  result = byte_45B8CA;
  if ( !byte_45B8CA )
  {
    result = dword_44F9A8;
    if ( dword_44F9A8 )
    {
      v2 = dword_44F9C4;
      v8 = dword_44F9C4;
      v9 = dword_44F9A8;
      do
      {
        if ( !strcmp(a1, (const char *)v2 - 20) && (unsigned __int8)dword_4F831C < 0x10u )
        {
          v3 = *v2;
          v4 = *(v2 - 1);
          v5 = 2 * (unsigned __int8)dword_4F831C;
          dword_5B6DC0[v5] = v3;
          dword_5B6DC4[v5] = v4;
          if ( !sub_41BD60(v4, v3) )
          {
            v6 = dword_4F831C + 1;
            dword_5B6DC0[v5] = v3;
            dword_5B6DC4[v5] = v4;
            LOBYTE(dword_4F831C) = v6;
          }
          v2 = v8;
        }
        v2 += 6;
        result = v9 - 1;
        v7 = v9 == 1;
        v8 = v2;
        --v9;
      }
      while ( !v7 );
    }
  }
  return result;
}
