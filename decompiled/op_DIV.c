#include "pch.h"
int op_DIV()
{
  int v0; // ecx
  int v1; // esi
  int result; // eax

  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rs_0 = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = BYTE2(cpu_opcode) & 0x1F;
  v1 = cpu_gpr[v0];
  if ( v1 )
  {
    cpu_LO = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / v1;
    result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / cpu_gpr[v0];
    cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] % cpu_gpr[v0];
  }
  else
  {
    cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
    cpu_LO = -1;
    return dbg_print(" division sign by 0 \n");
  }
  return result;
}
