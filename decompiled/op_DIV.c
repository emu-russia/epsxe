#include "pch.h"
int sub_41E3A0()
{
  int v0; // ecx
  int v1; // esi
  int result; // eax

  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  unk_576DAF = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  v0 = BYTE2(cpu_opcode) & 0x1F;
  v1 = cpu_gpr[v0];
  if ( v1 )
  {
    LODWORD(cpu_LO) = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / v1;
    result = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] / cpu_gpr[v0];
    HIDWORD(cpu_LO) = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] % cpu_gpr[v0];
  }
  else
  {
    HIDWORD(cpu_LO) = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F];
    LODWORD(cpu_LO) = -1;
    return dbg_print(aDivisionSignBy);
  }
  return result;
}
