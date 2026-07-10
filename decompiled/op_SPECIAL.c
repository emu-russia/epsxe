#include "pch.h"
void __noreturn op_SPECIAL()
{
  cpu_special_opcode_table[cpu_opcode & 0x3F]();
}
