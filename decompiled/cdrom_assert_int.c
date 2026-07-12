#include "pch.h"
void cdrom_assert_int()
{
  *(_DWORD *)int_reg |= 4u;
}
