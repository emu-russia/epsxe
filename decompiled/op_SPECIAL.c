#include "pch.h"
void __noreturn cpu_execute_special_opcode()
{
  cpu_special_opcode_table[cpu_opcode & 0x3F]();
}
