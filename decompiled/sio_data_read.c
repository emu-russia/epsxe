#include "pch.h"
void sio_data_read()
{
  if ( dword_4FD86C && dword_50C270 < (unsigned int)dword_4FD864 )
  {
    dword_4FD86C = 0;
    sub_421FD0();
  }
  if ( MEMORY[0x52680F] != (_BYTE)dword_526810 && ++MEMORY[0x52680F] == (_BYTE)dword_526810 )
    LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFD;
}
