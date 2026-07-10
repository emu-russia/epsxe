#include "pch.h"
int __cdecl sub_439F60(int a1, int a2, unsigned int a3)
{
  unsigned int v3; // ebp
  int v4; // ebx
  const void *v5; // esi
  unsigned int v7; // eax
  unsigned __int8 *v8; // esi
  int v9; // ecx
  int v10; // eax
  unsigned int v11; // edx
  int v12; // edi
  int v13; // eax

  v3 = a3;
  if ( !a1 )
    return -2;
  v4 = *(_DWORD *)(a1 + 28);
  if ( !v4 )
    return -2;
  v5 = (const void *)a2;
  if ( !a2 || *(_DWORD *)(v4 + 4) != 42 )
    return -2;
  *(_DWORD *)(a1 + 48) = sub_43C450(*(_DWORD *)(a1 + 48), a2, a3);
  if ( a3 < 3 )
    return 0;
  v7 = *(_DWORD *)(v4 + 36) - 262;
  if ( a3 > v7 )
  {
    v3 = *(_DWORD *)(v4 + 36) - 262;
    v5 = (const void *)(a3 - v7 + a2);
  }
  qmemcpy(*(void **)(v4 + 48), v5, v3);
  v8 = *(unsigned __int8 **)(v4 + 48);
  v9 = *(_DWORD *)(v4 + 80);
  *(_DWORD *)(v4 + 100) = v3;
  *(_DWORD *)(v4 + 84) = v3;
  v10 = *v8;
  *(_DWORD *)(v4 + 64) = v10;
  v11 = 0;
  *(_DWORD *)(v4 + 64) = *(_DWORD *)(v4 + 76) & (v8[1] ^ (v10 << v9));
  do
  {
    v12 = *(_DWORD *)(v4 + 60);
    v13 = *(_DWORD *)(v4 + 76)
        & ((*(_DWORD *)(v4 + 64) << *(_DWORD *)(v4 + 80))
         ^ *(unsigned __int8 *)(*(_DWORD *)(v4 + 48) + v11 + 2));
    *(_DWORD *)(v4 + 64) = v13;
    *(_WORD *)(*(_DWORD *)(v4 + 56) + 2 * (*(_DWORD *)(v4 + 44) & v11)) = *(_WORD *)(v12 + 2 * v13);
    *(_WORD *)(*(_DWORD *)(v4 + 60) + 2 * *(_DWORD *)(v4 + 64)) = v11++;
  }
  while ( v11 <= v3 - 3 );
  return 0;
}
