#include "pch.h"
void __cdecl gpu_unfreeze(int a1, _DWORD *ArgList)
{
  char *v2; // esi
  char v3[16]; // [esp+0h] [ebp-10h] BYREF

  if ( GPUfreeze )
  {
    v2 = (char *)malloc(0x100408u);
    gzread(ArgList, v3, 7);
    gzread(ArgList, v2, 1049608);
    GPUfreeze(0, v2);
    free(v2);
  }
  else
  {
    gzread(ArgList, v3, 7);
    dbg_print(" * GPU plugin doesn't support savestates. \n");
  }
}
