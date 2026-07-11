#include "pch.h"
void __noreturn op_UNKNOWN()
{
  ui_error(
    "\nePSXe: Opcode [%02x-%08x] in PC [%08x] UNKNOWN [%08x:%03d:%d]\n",
    (unsigned int)cpu_opcode >> 26,
    cpu_opcode,
    reg_pc - 4,
    dword_50C360,
    dword_50C364,
    hw_update_counter);
}
