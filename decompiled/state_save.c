#include "pch.h"
_DWORD *state_save()
{
  _DWORD *result; // eax
  _DWORD *v1; // esi
  char v2[64]; // [esp+8h] [ebp-440h] BYREF
  char Buffer[1024]; // [esp+48h] [ebp-400h] BYREF

  sprintf(Buffer, "%s%s.%03d", "sstates\\", byte_8B3D80, (unsigned __int8)gpu_freeze_counter);
  memset(v2, 0, sizeof(v2));
  result = gzopen(Buffer, "wb1");
  v1 = result;
  if ( result )
  {
    sprintf(v2, "ePSXe");
    if ( save_state_ver == -1 )
      *(_WORD *)&v2[5] = 2;
    else
      *(_WORD *)&v2[5] = save_state_ver;
    *(_DWORD *)&v2[7] = *(_DWORD *)byte_8B3D80;
    *(_DWORD *)&v2[11] = dword_8B3D84;
    *(_DWORD *)&v2[15] = dword_8B3D88;
    gzwrite((int)v1, (unsigned __int8 *)v2, 0x40u);
    sprintf(v2, "PSX");
    *(_DWORD *)&v2[3] = 364;
    gzwrite((int)v1, (unsigned __int8 *)v2, 7u);
    gzwrite((int)v1, (unsigned __int8 *)reg_pc, 0x16Cu);
    mem_freeze("MEM", (int)v1);
    sub_423780("REG", (int)v1);
    sub_42B080("IRQ", (int)v1);
    gte_freeze("GTE", (int)v1);
    cdr_freeze("CDR", (int)v1);
    sio_freeze("SIO", (int)v1);
    if ( save_state_ver == -1 )
      sub_42A0D0("MDE", (int)v1);
    else
      sub_42A160("MDE", (int)v1);
    gpu_freeze("GPU", (int)v1, Buffer);
    spu_freeze_cb("SPU", v1);
    return (_DWORD *)gzclose(v1);
  }
  return result;
}
