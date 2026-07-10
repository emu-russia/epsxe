#include "pch.h"
void sio_assert_int()
{
  int_reg |= 0x80u;
}
