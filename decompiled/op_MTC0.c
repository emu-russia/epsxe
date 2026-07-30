#include "pch.h"
unsigned int op_MTC0()
{
  unsigned __int8 v0; // cl
  unsigned __int8 v1; // al
  unsigned int result; // eax
  int v3; // edx
  int v4; // edx

  v0 = ((unsigned int)cpu_opcode >> 11) & 0x1F;
  v1 = BYTE2(cpu_opcode) & 0x1F;
  op_rt = BYTE2(cpu_opcode) & 0x1F;
  op_rd = v0;
  if ( v0 == 14 || v0 == 15 || v0 == 8 )
    return dbg_print("[%d] only read!!!\n", (unsigned __int16)cpu_opcode >> 11);
  if ( v0 == 13 )
  {
    result = cpu_gpr[v1];
    dword_50C2A8 = result;
    if ( (result & 0x100) != 0 && (dword_50C2A4 & 0x101) == 0x101 )
    {
LABEL_21:
      result = dword_50C2A4;
      if ( (dword_50C2A4 & 0x101) == 0x101 )
      {
        result = dword_50C2A4 & 0xFFFFFFC0;
        dword_50C2AC = *(_DWORD *)reg_pc;
        dword_50C2A8 = 256;
        *(_DWORD *)reg_pc = 0x80000080;
        dword_50C2A4 = dword_50C2A4 & 0xFFFFFFC0 | (4 * (dword_50C2A4 & 0xF));
      }
    }
  }
  else if ( v0 == 12 )
  {
    result = cpu_gpr[v1];
    dword_50C2A4 = result;
    if ( (dword_50C2A8 & 0x100) != 0 )
    {
      result &= 0x101u;
      if ( result == 257 )
        goto LABEL_21;
    }
  }
  else
  {
    if ( v0 == 3 )
    {
      if ( byte_4F8320 )
      {
        byte_4F8320 = 0;
        cpu_gpr[v1] |= 1u;
      }
      else
      {
        v3 = cpu_gpr[v1];
        if ( dword_50C280[0] != v3 )
        {
          v4 = v3 | 1;
          if ( dword_50C280[0] == v4 )
            cpu_gpr[v1] = v4;
        }
      }
    }
    cop0_regs[v0] = cpu_gpr[v1];
    return v0;
  }
  return result;
}
