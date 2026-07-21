#include "pch.h"
void __cdecl mem_hw_reg_read_byte(unsigned int a1)
{
  hw_update_counter -= 4;
  if ( (a1 & 0x1FC00000) != 0x1F800000 || (unsigned __int16)a1 < 0x1000u )
    return;
  if ( a1 >= 0x1F801C00 && a1 <= 0x1F801EEF )
  {
    spu_read_register_cb(a1);
    return;
  }
  if ( a1 > 0x1F801801 )
  {
    if ( a1 == 0x1F801802 )
    {
      ++dword_50BF5C;
      return;
    }
    if ( a1 == 0x1F801803 )
      return;
LABEL_19:
    dump_log(console_log_handle, "REG %s [%08x] -> %08x sizeof(%d)\n", "UNK", a1, 0, 1);
    return;
  }
  if ( a1 == 0x1F801801 )
  {
    if ( (unsigned __int8)byte_50AEC1 < (unsigned __int8)byte_50AEC0 )
    {
      if ( byte_50AEC2 )
      {
        if ( (unsigned __int8)++byte_50AEC1 >= (unsigned __int8)byte_50AEC0 )
          byte_50AEC2 = 0;
      }
    }
    return;
  }
  if ( a1 == 528486464 )
  {
    sio_read_data_byte();
    return;
  }
  if ( a1 != 528486646 && a1 != 528488448 )
    goto LABEL_19;
}
