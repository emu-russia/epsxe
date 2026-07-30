#include "pch.h"
char op_BLTZ()
{
  unsigned int v0; // ecx
  int v1; // eax

  v0 = (unsigned __int16)cpu_opcode;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  op_ofs = (unsigned __int16)cpu_opcode;
  if ( (cpu_opcode & 0x8000) != 0 )
  {
    v0 = cpu_opcode | 0xFFFF0000;
    op_ofs = v0;
  }
  v1 = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
  if ( v1 < 0 )
  {
    cpu_opcode = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
    *(_DWORD *)reg_pc += 4 * v0;
    LOBYTE(v1) = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
    --hw_update_counter;
  }
  return v1;
}
