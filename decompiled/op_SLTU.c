#include "pch.h"
__int64 op_SLTU()
{
  __int64 result; // rax

  byte_576DB0 = BYTE2(cpu_opcode) & 0x1F;
  unk_576DAF = ((unsigned int)cpu_opcode >> 21) & 0x1F;
  byte_576DAD = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  LODWORD(result) = (unsigned __int16)cpu_opcode >> 11;
  HIDWORD(result) = cpu_gpr[((unsigned int)cpu_opcode >> 21) & 0x1F] < (unsigned int)cpu_gpr[BYTE2(cpu_opcode) & 0x1F];
  cpu_gpr[(_DWORD)result] = HIDWORD(result);
  return result;
}
