#include "pch.h"
int sub_403720()
{
  int v0; // ebx
  int v1; // ebp
  int result; // eax
  void *v3; // esi
  unsigned __int16 v4; // di
  _BYTE v5[5]; // [esp+10h] [ebp-440h] BYREF
  int v6; // [esp+15h] [ebp-43Bh]
  char Buffer[1024]; // [esp+50h] [ebp-400h] BYREF

  v0 = dword_50C36C;
  v1 = dword_50C37C;
  if ( !strcmp(unk_8B5180, aNull) )
  {
    sprintf(Buffer, "%s%s.%03d", aSstates, byte_8B3D80, (unsigned __int8)gpu_freeze_counter);
  }
  else
  {
    sprintf(Buffer, "%s", unk_8B5180);
    sprintf(unk_8B5180, "NULL");
  }
  result = sub_4386F0(Buffer, (int)aRb1);
  v3 = (void *)result;
  if ( result )
  {
    sub_438CA0(result, v5, 64);
    v4 = v6;
    sub_438CA0(v3, v5, 7);
    sub_438CA0(v3, &reg_pc, 364);
    dword_50C36C = v0;
    dword_50C37C = v1;
    mem_unfreeze((int)aMem, (int)v3);
    sub_4237F0((int)aReg, (int)v3);
    sub_42B120(aIrq, v3);
    gte_unfreeze((int)aGte, (int)v3);
    if ( v4 >= 2u )
      sub_42CED0(aCdr, v3);
    else
      sub_42CF40(aCdr, v3);
    sio_unfreeze(aSio, v3);
    if ( v4 )
      sub_42A1B0((int)aMde, (int)v3);
    else
      sub_42A210((int)aMde, (int)v3);
    gpu_unfreeze((int)aGpu, (int)v3);
    spu_unfreeze_cb(aSpu, v3);
    return sub_439420(v3);
  }
  return result;
}
