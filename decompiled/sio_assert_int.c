#include "pch.h"
void sio_assert_int()
{
  *(_DWORD *)int_reg |= 0x80u;
}
