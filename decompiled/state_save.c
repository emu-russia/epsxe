#include "pch.h"
void *state_save()
{
  void *result; // eax
  void *v1; // esi
  char v2[64]; // [esp+8h] [ebp-440h] BYREF
  char Buffer[1024]; // [esp+48h] [ebp-400h] BYREF

  sprintf(Buffer, "%s%s.%03d", aSstates, byte_8B3D80, (unsigned __int8)gpu_freeze_counter);
  memset(v2, 0, sizeof(v2));
  result = (void *)sub_4386F0(Buffer, (int)aWb1);
  v1 = result;
  if ( result )
  {
    sprintf(v2, aEpsxe);
    if ( byte_44C0AC == -1 )
      *(_WORD *)&v2[5] = 2;
    else
      *(_WORD *)&v2[5] = byte_44C0AC;
    *(_DWORD *)&v2[7] = *(_DWORD *)byte_8B3D80;
    *(_DWORD *)&v2[11] = unk_8B3D84;
    *(_DWORD *)&v2[15] = unk_8B3D88;
    sub_438F70((int)v1, (int)v2, 64);
    sprintf(v2, aPsx);
    *(_DWORD *)&v2[3] = 364;
    sub_438F70((int)v1, (int)v2, 7);
    sub_438F70((int)v1, (int)&reg_pc, 364);
    mem_freeze(aMem, (int)v1);
    sub_423780(aReg, (int)v1);
    sub_42B080(aIrq, (int)v1);
    gte_freeze(aGte, (int)v1);
    cdr_freeze(aCdr, (int)v1);
    sio_freeze(aSio, (int)v1);
    if ( byte_44C0AC == -1 )
      sub_42A0D0(aMde, (int)v1);
    else
      sub_42A160(aMde, (int)v1);
    gpu_freeze(aGpu, (int)v1, Buffer);
    spu_freeze_cb(aSpu, v1);
    return (void *)sub_439420(v1);
  }
  return result;
}
