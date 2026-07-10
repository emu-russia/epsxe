#include "pch.h"
void __cdecl gpu_freeze(int a1, int ArgList)
{
  void *v2; // esi
  _BYTE v3[16]; // [esp+0h] [ebp-10h] BYREF

  if ( GPUfreeze )
  {
    v2 = malloc(0x100408u);
    sub_438CA0(ArgList, v3, 7);
    sub_438CA0(ArgList, v2, 1049608);
    GPUfreeze(0, v2);
    free(v2);
  }
  else
  {
    sub_438CA0(ArgList, v3, 7);
    dbg_print(aGpuPluginDoesn);
  }
}
