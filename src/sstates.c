#include "pch.h"
char gpu_freeze_with_counter()
{
  LOBYTE(gpu_freeze_counter) = ((unsigned __int8)gpu_freeze_counter + 1) % 5;
  gpu_do_freeze((unsigned __int8)gpu_freeze_counter);
  return gpu_freeze_counter;
}

char __cdecl set_gpu_freeze_counter(char a1)
{
  LOBYTE(gpu_freeze_counter) = a1;
  return a1;
}

char get_gpu_freeze_counter()
{
  return gpu_freeze_counter;
}

_DWORD *state_save()
{
  _DWORD *result; // eax
  _DWORD *v1; // esi
  char v2[64]; // [esp+8h] [ebp-440h] BYREF
  char Buffer[1024]; // [esp+48h] [ebp-400h] BYREF

  sprintf(Buffer, "%s%s.%03d", "sstates\\", default_filename, (unsigned __int8)gpu_freeze_counter);
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
    *(_DWORD *)&v2[7] = *(_DWORD *)default_filename;
    *(_DWORD *)&v2[11] = *(_DWORD *)&default_filename[4];
    *(_DWORD *)&v2[15] = *(_DWORD *)&default_filename[8];
    gzwrite((int)v1, (unsigned __int8 *)v2, 0x40u);
    sprintf(v2, "PSX");
    *(_DWORD *)&v2[3] = 364;
    gzwrite((int)v1, (unsigned __int8 *)v2, 7u);
    gzwrite((int)v1, (unsigned __int8 *)reg_pc, 0x16Cu);
    mem_freeze("MEM", (int)v1);
    hw_reg_freeze("REG", (int)v1);
    irq_freeze("IRQ", (int)v1);
    gte_freeze("GTE", (int)v1);
    cdr_freeze("CDR", (int)v1);
    sio_freeze("SIO", (int)v1);
    if ( save_state_ver == -1 )
      mdec_freeze("MDE", (int)v1);
    else
      mdec_freeze2("MDE", (int)v1);
    gpu_freeze("GPU", (int)v1, Buffer);
    spu_freeze_cb("SPU", v1);
    return (_DWORD *)gzclose(v1);
  }
  return result;
}

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

  v0 = dynarec_enabled;
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
    dynarec_enabled = v0;
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

char __cdecl check_state_exists(unsigned __int8 a1)
{
  FILE *v1; // eax
  char Buffer[1024]; // [esp+0h] [ebp-400h] BYREF

  sprintf(Buffer, "%s%s.%03d", "sstates\\", default_filename, a1);
  v1 = fopen(Buffer, "rb");
  if ( !v1 )
    return -1;
  fclose(v1);
  return 0;
}


/* Decompiled globals (previously generated in src/_gen) */
unsigned int gpu_freeze_counter = 0x0;
unsigned char save_state_ver = 0xff;
unsigned char state_file_from_cmdline[0x400];
