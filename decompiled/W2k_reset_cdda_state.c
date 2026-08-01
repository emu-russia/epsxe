#include "pch.h"
void W2k_reset_cdda_state()
{
  dword_4FD9D8 = 0;
  dword_457348 = -1;
  cdr_spinup_motor();
}
