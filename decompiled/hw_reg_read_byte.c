#include "pch.h"
char __cdecl hw_reg_read_byte(unsigned int a1)
{
  char result; // al

  dword_50C270 -= 4;
  if ( (a1 & 0x1FC00000) != 0x1F800000 )
    return *(_BYTE *)((unsigned __int16)a1 + ram[HIWORD(a1)]);
  if ( (unsigned __int16)a1 < 0x1000u )
    return *((_BYTE *)&dcache + (a1 & 0xFFF));
  if ( a1 >= 0x1F801C00 && a1 <= 0x1F801EEF )
    return spu_read_register_cb(a1);
  if ( a1 > 0x1F801801 )
  {
    if ( a1 == 0x1F801802 )
      return byte_50AF56[dword_50BF5C++];
    if ( a1 == 0x1F801803 )
      return byte_50AF44[1];
    goto LABEL_20;
  }
  if ( a1 != 0x1F801801 )
  {
    switch ( a1 )
    {
      case 0x1F801040u:
        return sio_data_read();
      case 0x1F8010F6u:
        return BYTE2(dword_50BFC8);
      case 0x1F801800u:
        if ( byte_50AEC2 && (unsigned __int8)byte_50AEC1 < (unsigned __int8)byte_50AEC0 )
          return byte_50AF48 | 0x28;
        else
          return byte_50AF48 & 0xD7 | 8;
    }
LABEL_20:
    dump_log(console_log_handle, "REG %s [%08x] -> %08x sizeof(%d)\n", (const char *)&off_455894, a1, 0, 1);
    return 0;
  }
  result = 0;
  if ( (unsigned __int8)byte_50AEC1 < (unsigned __int8)byte_50AEC0 )
  {
    if ( byte_50AEC2 )
    {
      result = *((_BYTE *)&dword_50AE80 + (unsigned __int8)byte_50AEC1++);
      if ( (unsigned __int8)byte_50AEC1 >= (unsigned __int8)byte_50AEC0 )
        byte_50AEC2 = 0;
    }
  }
  return result;
}
