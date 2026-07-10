#include "pch.h"
int __cdecl sub_43B400(int a1, unsigned __int8 *a2, unsigned int a3)
{
  unsigned __int8 *v3; // ecx
  unsigned int v5; // esi
  unsigned int v6; // eax
  unsigned int v7; // edi
  unsigned int v8; // eax
  unsigned __int8 *v9; // ecx
  int v10; // ebx
  unsigned int v11; // edx
  int v12; // eax
  int v13; // ebx
  unsigned int v14; // eax
  int v15; // edx
  int v16; // ebx
  unsigned int v17; // edx
  int v18; // eax
  int v19; // ebx
  unsigned int v20; // eax
  int v21; // edx
  int v22; // ebx
  unsigned int v23; // edx
  unsigned int v24; // eax

  v3 = a2;
  if ( !a2 )
    return 0;
  v5 = a3;
  v6 = ~a1;
  if ( a3 >= 8 )
  {
    v7 = a3 >> 3;
    do
    {
      v5 -= 8;
      v8 = (v6 >> 8) ^ crc32_tab[*v3 ^ (unsigned __int8)v6];
      v9 = v3 + 1;
      v10 = v9[1];
      v11 = (v8 >> 8) ^ crc32_tab[*v9++ ^ (unsigned __int8)v8];
      v12 = v10 ^ (unsigned __int8)v11;
      v13 = v9[1];
      v14 = (v11 >> 8) ^ crc32_tab[v12];
      ++v9;
      v15 = v13 ^ (unsigned __int8)v14;
      v16 = v9[1];
      v17 = (v14 >> 8) ^ crc32_tab[v15];
      ++v9;
      v18 = v16 ^ (unsigned __int8)v17;
      v19 = v9[1];
      v20 = (v17 >> 8) ^ crc32_tab[v18];
      ++v9;
      v21 = v19 ^ (unsigned __int8)v20;
      v22 = v9[1];
      v23 = (v20 >> 8) ^ crc32_tab[v21];
      ++v9;
      v24 = (v23 >> 8) ^ crc32_tab[v22 ^ (unsigned __int8)v23];
      v6 = crc32_tab[v9[1] ^ (unsigned __int8)v24] ^ (v24 >> 8);
      v3 = v9 + 2;
      --v7;
    }
    while ( v7 );
  }
  for ( ; v5; --v5 )
    v6 = crc32_tab[*v3++ ^ (unsigned __int8)v6] ^ (v6 >> 8);
  return ~v6;
}
