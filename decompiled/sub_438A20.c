#include "pch.h"
char __cdecl sub_438A20(int *a1)
{
  int v1; // ebx
  int *v2; // edi
  int v3; // eax
  int v4; // edi
  int v5; // eax
  char v6; // bl
  int v7; // edi
  int v8; // edi
  int v9; // ecx
  int v10; // edi
  int i; // eax
  int j; // eax
  int v14; // edi
  int v15; // ecx
  int v16; // eax

  v1 = 0;
  v2 = &dword_4574E0;
  while ( 1 )
  {
    v3 = sub_438B70((int)a1);
    if ( v3 != *v2 )
      break;
    ++v2;
    ++v1;
    if ( v2 >= (int *)a113 )
    {
      v4 = sub_438B70((int)a1);
      LOBYTE(v5) = sub_438B70((int)a1);
      v6 = v5;
      if ( v4 != 8 || (v5 & 0xE0) != 0 )
      {
        a1[14] = -3;
      }
      else
      {
        v7 = 6;
        do
        {
          sub_438B70((int)a1);
          --v7;
        }
        while ( v7 );
        if ( (v6 & 4) != 0 )
        {
          v8 = sub_438B70((int)a1);
          v9 = (sub_438B70((int)a1) << 8) + v8;
          v10 = v9 - 1;
          if ( v9 )
          {
            do
            {
              if ( sub_438B70((int)a1) == -1 )
                break;
            }
            while ( v10-- );
          }
        }
        if ( (v6 & 8) != 0 )
        {
          for ( i = sub_438B70((int)a1); i; i = sub_438B70((int)a1) )
          {
            if ( i == -1 )
              break;
          }
        }
        if ( (v6 & 0x10) != 0 )
        {
          for ( j = sub_438B70((int)a1); j; j = sub_438B70((int)a1) )
          {
            if ( j == -1 )
              break;
          }
        }
        if ( (v6 & 2) != 0 )
        {
          v14 = 2;
          do
          {
            sub_438B70((int)a1);
            --v14;
          }
          while ( v14 );
        }
        v5 = -(a1[15] != 0);
        LOBYTE(v5) = v5 & 0xFD;
        a1[14] = v5;
      }
      return v5;
    }
  }
  if ( v1 )
  {
    v15 = *a1 - 1;
    ++a1[1];
    *a1 = v15;
  }
  if ( v3 != -1 )
  {
    v16 = *a1 - 1;
    ++a1[1];
    *a1 = v16;
    a1[22] = 1;
  }
  v5 = a1[1] == 0;
  a1[14] = v5;
  return v5;
}
