#include "pch.h"
int gte_clear_regs()
{
  memset(&gte_regs, 0, sizeof(gte_regs));
  return 0;
}
