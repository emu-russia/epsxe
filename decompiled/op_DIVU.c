#include "pch.h"
unsigned int sub_41E430()
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
    LODWORD(cpu_LO) = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / v1;
    result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / (unsigned int)cpu_gpr[v0];
    HIDWORD(cpu_LO) = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] % (unsigned int)cpu_gpr[v0];
  }
  else
  {
    HIDWORD(cpu_LO) = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
    LODWORD(cpu_LO) = -1;
    return dbg_print(aDivisionBy0);
  }
  return result;
}
