#include "pch.h"
void __cdecl spu_freeze(const char *a1, int a2)
{
  size_t v2; // edi
  unsigned __int8 *v3; // esi
  char Buffer[3]; // [esp+8h] [ebp-40h] BYREF
  int v5; // [esp+Bh] [ebp-3Dh]
  size_t Size; // [esp+14h] [ebp-34h]

  sprintf(Buffer, "%s", a1);
  v5 = 0;
  gzwrite(a2, (unsigned __int8 *)Buffer, 7u);
  if ( SPUfreeze )
  {
    SPUfreeze(2, Buffer);
    v2 = Size;
    if ( Size )
    {
      v3 = (unsigned __int8 *)malloc(Size);
      SPUfreeze(1, v3);
      gzwrite(a2, v3, v2);
      free(v3);
    }
  }
  else
  {
    dbg_print(" * SPU plugin doesn't support savestates. \n");
  }
}
