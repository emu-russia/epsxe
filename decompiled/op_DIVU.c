#include "pch.h"
unsigned int op_DIVU()
{
  int v0; // ecx
  unsigned int v1; // esi
  unsigned int result; // eax

  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  unk_576DAF = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = BYTE2(cpu_opcode) & 0x1F;
  v1 = cpu_gpr[v0];
  if ( v1 )
  {
    cpu_LO = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / v1;
    result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / (unsigned int)cpu_gpr[v0];
    cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] % (unsigned int)cpu_gpr[v0];
  }
  else
  {
    cpu_HI = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
    cpu_LO = -1;
    return dbg_print(" division by 0 \n");
  }
  return result;
}
