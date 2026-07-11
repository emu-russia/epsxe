#include "pch.h"
int __cdecl sio_read_word(int a1)
{
  char v2; // al
  unsigned __int16 v3; // bx
  char v4; // al
  unsigned __int8 v5; // al
  int v6; // ebx
  unsigned __int8 v7; // al

  if ( a1 == 0x1F801040 )
  {
    sio_data_read();
    HIBYTE(v3) = v2;
    sio_data_read();
    LOBYTE(v3) = v4;
    sio_data_read();
    v6 = (v5 | (v3 << 8)) << 8;
    sio_data_read();
    return v6 | v7;
  }
  else if ( a1 == 0x1F801044 )
  {
    if ( dword_4FD86C )
    {
      if ( hw_update_counter < (unsigned int)dword_4FD864 )
      {
        dword_4FD86C = 0;
        sub_421FD0();
      }
    }
    return (unsigned __int16)sio0_mode_reg;
  }
  else
  {
    return 0;
  }
}
