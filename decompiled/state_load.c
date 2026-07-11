#include "pch.h"
_DWORD *state_load()
{
  int v0; // ebx
  int v1; // ebp
  _DWORD *result; // eax
  _DWORD *v3; // esi
  unsigned __int16 v4; // di
  char v5[5]; // [esp+10h] [ebp-440h] BYREF
  int v6; // [esp+15h] [ebp-43Bh]
  char Buffer[1024]; // [esp+50h] [ebp-400h] BYREF

  v0 = dword_50C36C;
  v1 = dword_50C37C;
  if ( !strcmp(state_file_from_cmdline, "NULL") )
  {
    sprintf(Buffer, "%s%s.%03d", "sstates\\", byte_8B3D80, (unsigned __int8)gpu_freeze_counter);
  }
  else
  {
    sprintf(Buffer, "%s", state_file_from_cmdline);
    sprintf(state_file_from_cmdline, "NULL");
  }
  result = gzopen(Buffer, "rb1");
  v3 = result;
  if ( result )
  {
    gzread(result, v5, 64);
    v4 = v6;
    gzread(v3, v5, 7);
    gzread(v3, reg_pc, 364);
    dword_50C36C = v0;
    dword_50C37C = v1;
    mem_unfreeze((int)"MEM", (int)v3);
    hw_reg_unfreeze((int)"REG", v3);
    irq_unfreeze((int)"IRQ", (int)v3);
    gte_unfreeze((int)"GTE", (int)v3);
    if ( v4 >= 2u )
      sub_42CED0((int)"CDR", (int)v3);
    else
      sub_42CF40("CDR", v3);
    sio_unfreeze((int)"SIO", (int)v3);
    if ( v4 )
      sub_42A1B0((int)"MDE", (int)v3);
    else
      sub_42A210((int)"MDE", (int)v3);
    gpu_unfreeze((int)"GPU", (int)v3);
    spu_unfreeze_cb("SPU", v3);
    return (_DWORD *)gzclose(v3);
  }
  return result;
}
