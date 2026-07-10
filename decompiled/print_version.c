#include "pch.h"
void __noreturn print_version()
{
  dbg_print_no_flush(" * %s emulator version %1.1f.%d. %s\n", "ePSXe", 1.6, 0, &byte_45B8CC);
  exit(0);
}
