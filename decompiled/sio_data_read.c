#include "pch.h"
void sio_data_read()
{
  if ( dword_4FD86C && hw_update_counter < (unsigned int)dword_4FD864 )
  {
    dword_4FD86C = 0;
    sub_421FD0();
  }
  if ( byte_52670C[259] != (_BYTE)dword_526810 && ++byte_52670C[259] == (_BYTE)dword_526810 )
    LOBYTE(sio0_mode_reg) = sio0_mode_reg & 0xFD;
}
