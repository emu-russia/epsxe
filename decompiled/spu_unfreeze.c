#include "pch.h"
void __cdecl spu_unfreeze(int a1, _DWORD *a2)
{
  size_t v2; // ebx
  void *v3; // esi
  char v4[4]; // [esp+8h] [ebp-40h] BYREF
  int v5; // [esp+Ch] [ebp-3Ch]
  int v6; // [esp+10h] [ebp-38h]
  size_t Size; // [esp+14h] [ebp-34h]

  gzread(a2, v4, 7);
  if ( SPUfreeze )
  {
    gzread(a2, v4, 16);
    v2 = Size;
    if ( Size )
    {
      v3 = malloc(Size);
      *(_DWORD *)v3 = *(_DWORD *)v4;
      *((_DWORD *)v3 + 1) = v5;
      *((_DWORD *)v3 + 2) = v6;
      *((_DWORD *)v3 + 3) = Size;
      gzread(a2, (char *)v3 + 16, v2 - 16);
      SPUfreeze(0, v3);
      free(v3);
    }
  }
  else
  {
    dbg_print(" * SPU plugin doesn't support savestates. \n");
  }
}
