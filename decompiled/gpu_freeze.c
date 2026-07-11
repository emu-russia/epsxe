#include "pch.h"
void __cdecl gpu_freeze(const char *a1, int ArgList, const char *a3)
{
  unsigned __int8 *v3; // esi
  void *v4; // esi
  FILE *v5; // edi
  char Buffer[3]; // [esp+8h] [ebp-410h] BYREF
  int v7; // [esp+Bh] [ebp-40Dh]
  char FileName[1024]; // [esp+18h] [ebp-400h] BYREF

  if ( GPUfreeze )
  {
    v3 = (unsigned __int8 *)malloc(0x100408u);
    *(_DWORD *)v3 = 1;
    sprintf(Buffer, "%s", a1);
    v7 = 1049608;
    GPUfreeze(1, v3);
    gzwrite(ArgList, (unsigned __int8 *)Buffer, 7u);
    gzwrite(ArgList, v3, 0x100408u);
    free(v3);
    if ( GPUgetScreenPic )
    {
      v4 = malloc(0x9000u);
      sprintf(FileName, "%s.pic", a3);
      GPUgetScreenPic(v4);
      v5 = fopen(FileName, "wb");
      fwrite(v4, 1u, 0x9000u, v5);
      fclose(v5);
      free(v4);
    }
  }
  else
  {
    sprintf(Buffer, "%s", a1);
    v7 = 0;
    gzwrite(ArgList, (unsigned __int8 *)Buffer, 7u);
    dbg_print(" * GPU plugin doesn't support savestates. \n");
  }
}
