#include "pch.h"
void __noreturn sub_42AC80()
{
  cpu_bcond_opcode_table[BYTE2(cpu_opcode) & 0x1F]();
}
