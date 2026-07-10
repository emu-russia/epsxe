#include "pch.h"
void __cdecl gpu_unfreeze(const char *a1, int ArgList, const char *a3)
{
  _DWORD *v3; // esi
  void *v4; // esi
  FILE *v5; // edi
  char Buffer[3]; // [esp+8h] [ebp-410h] BYREF
  int v7; // [esp+Bh] [ebp-40Dh]
  char FileName[1024]; // [esp+18h] [ebp-400h] BYREF

  if ( GPUfreeze )
  {
    v3 = malloc(0x100408u);
    *v3 = 1;
    sprintf(Buffer, "%s", a1);
    v7 = 1049608;
    GPUfreeze(1, v3);
    sub_438F70(ArgList, Buffer, 7);
    sub_438F70(ArgList, v3, 1049608);
    free(v3);
    if ( GPUgetScreenPic )
    {
      v4 = malloc(0x9000u);
      sprintf(FileName, "%s.pic", a3);
      GPUgetScreenPic(v4);
      v5 = fopen(FileName, aWb);
      fwrite(v4, 1u, 0x9000u, v5);
      fclose(v5);
      free(v4);
    }
  }
  else
  {
    sprintf(Buffer, "%s", a1);
    v7 = 0;
    sub_438F70(ArgList, Buffer, 7);
    dbg_print(aGpuPluginDoesn);
  }
}
