#include "pch.h"
char op_JAL()
{
  int v0; // ecx
  char result; // al

  op_jump_addr = cpu_opcode & 0x3FFFFFF;
  v0 = 4 * (cpu_opcode & 0x3FFFFFF);
  cpu_opcode = *(_DWORD *)(*(unsigned __int16 *)reg_pc + mem_read_hooks[*(unsigned __int16 *)&reg_pc[2]]);
  cpu_gpr[31] = *(_DWORD *)reg_pc + 4;
  *(_DWORD *)reg_pc = v0 | *(_DWORD *)reg_pc & 0xF0000000;
  result = cpu_main_table[(unsigned int)cpu_opcode >> 26]();
  --hw_update_counter;
  return result;
}
