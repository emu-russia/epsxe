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
  v1 = loaded_file_type;
  if ( !strcmp(state_file_from_cmdline, "NULL") )
  {
    sprintf(Buffer, "%s%s.%03d", "sstates\\", default_filename, (unsigned __int8)gpu_freeze_counter);
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
    loaded_file_type = v1;
    mem_unfreeze((int)"MEM", v3);
    hw_reg_unfreeze((int)"REG", v3);
    irq_unfreeze((int)"IRQ", v3);
    gte_unfreeze((int)"GTE", v3);
    if ( v4 >= 2u )
      cdr_unfreeze_new((int)"CDR", v3);
    else
      cdr_unfreeze((int)"CDR", v3);
    sio_unfreeze((int)"SIO", v3);
    if ( v4 )
      mdec_unfreeze((int)"MDE", v3);
    else
      mdec_unfreeze2((int)"MDE", v3);
    gpu_unfreeze((int)"GPU", v3);
    spu_unfreeze_cb("SPU", v3);
    return (_DWORD *)gzclose(v3);
  }
  return result;
}
