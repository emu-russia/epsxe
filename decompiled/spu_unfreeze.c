#include "pch.h"
void __cdecl sub_40C120(int a1, int a2)
{
  size_t v2; // ebx
  _DWORD *v3; // esi
  _DWORD v4[3]; // [esp+8h] [ebp-40h] BYREF
  size_t Size; // [esp+14h] [ebp-34h]

  sub_438CA0(a2, v4, 7);
  if ( SPUfreeze )
  {
    sub_438CA0(a2, v4, 16);
    v2 = Size;
    if ( Size )
    {
      v3 = malloc(Size);
      *v3 = v4[0];
      v3[1] = v4[1];
      v3[2] = v4[2];
      v3[3] = Size;
      sub_438CA0(a2, v3 + 4, v2 - 16);
      SPUfreeze(0, v3);
      free(v3);
    }
  }
  else
  {
    dbg_print(aSpuPluginDoesn);
  }
}
