#include "pch.h"
char sub_431420()
{
  char result; // al
  void *v1; // esp
  _BYTE v2[8092]; // [esp+0h] [ebp-1F9Ch] BYREF

  if ( !byte_456D70 )
    return sub_42F870(byte_505420);
  if ( byte_456D70 == 1 )
    sub_42F7E0(byte_505420);
  if ( dword_50C37C == 3 )
  {
    result = iso_load(bin_iso_file);
    sound_use_cdda = 0;
  }
  else
  {
    dbg_print(aInitCoreW9xCdr);
    load_winaspi_dll();
    dbg_print(aOk_0);
    init_aspi();
    cdrom_gettrackinfo();
    v1 = alloca(8092);
    memset(v2, 0xAAu, sizeof(v2));
    dword_504C8C = 0;
    dword_4FFF80 = -1;
    sub_431900(0, 2, 16, 2, v2);
    result = v2[12];
    if ( !v2[12] && v2[13] == 2 && v2[14] == 22 && (result = v2[2364]) == 0 && v2[2365] == 2 && v2[2366] == 23 )
    {
      dword_504C8C = 1;
      dword_504C88 = 2352;
    }
    else if ( dword_504C8C != 1 )
    {
      memset(v2, 0xAAu, sizeof(v2));
      sub_431760(0, 2, 16, 2, v2);
      result = v2[12];
      if ( !v2[12] && v2[13] == 2 && v2[14] == 22 )
      {
        result = v2[2364];
        if ( !v2[2364] && v2[2365] == 2 && v2[2366] == 23 )
        {
          dword_504C8C = 7;
          dword_504C88 = 2352;
        }
      }
    }
  }
  return result;
}
