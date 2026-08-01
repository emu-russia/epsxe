#include "pch.h"
void W9x_reset_cdrom_state()
{
  dword_4FD9C0 = 0;
  dword_4FFF80 = -1;
  cdr_spinup_motor();
}
