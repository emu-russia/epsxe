#include "pch.h"
unsigned int cpu_load_bios_shell()
{
  int v0; // ecx
  unsigned int result; // eax
  int v2; // eax

  v0 = *(_DWORD *)reg_pc;
  result = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
  for ( cpu_opcode = result; *(_DWORD *)reg_pc != 0x80030000; cpu_opcode = result )
  {
    *(_DWORD *)reg_pc = v0 + 4;
    cpu_main_table[result >> 26]();
    v2 = --hw_update_counter;
    if ( hw_update_counter < 0 )
    {
      hw_update_counter = cpu_speed_scale + v2;
      if ( ++dword_50C364 >= (unsigned int)dword_45593C )
      {
        dword_50C364 = 0;
        ++dword_50C360;
      }
    }
    v0 = *(_DWORD *)reg_pc;
    result = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
  }
  return result;
}
