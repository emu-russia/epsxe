#include "pch.h"
void __noreturn op_BCONDZ()
{
  cpu_bcond_opcode_table[BYTE2(cpu_opcode) & 0x1F]();
}
