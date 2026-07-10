#include "pch.h"
void __noreturn op_COP0()
{
  cpu_cop0_table[((unsigned int)cpu_opcode >> 21) & 0x1F]();
}
